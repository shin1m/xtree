#include <iostream>
#include <vector>
#include <cassert>

#include "array.h"

template<typename T_value, size_t A_leaf, size_t A_branch>
std::string f_dump(const xtree::t_array<T_value, A_leaf, A_branch>& a_array)
{
	std::string s = R"(
)";
	a_array.f_dump([&](auto a_level, auto a_index)
	{
		s += std::string(a_level, ' ') + std::to_string(a_index) + R"(
)";
	});
	return s;
}

template<typename T_value, size_t A_leaf, size_t A_branch, typename T>
void f_assert_equals(const xtree::t_array<T_value, A_leaf, A_branch>& a0, const T& a1)
{
	assert(a0.f_size() == a1.size());
	assert(std::equal(a0.f_begin(), a0.f_end(), a1.begin(), a1.end()));
	auto i = a1.begin();
	for (size_t j = 0; j < a0.f_size(); ++j) assert(*a0.f_at(j) == *i++);
}

template<typename T_value, size_t A_leaf, size_t A_branch>
void f_assert_equals(const xtree::t_array<T_value, A_leaf, A_branch>& a0, std::initializer_list<T_value> a1)
{
	f_assert_equals<T_value, A_leaf, A_branch, std::initializer_list<T_value>>(a0, a1);
}

std::vector<int> f_range(int a_i, size_t a_n)
{
	std::vector<int> vector;
	for (size_t i = 0; i < a_n; ++i) vector.push_back(a_i++);
	return vector;
}

template<typename T_value, size_t A_leaf, size_t A_branch, typename T_iterator>
void f_test_insert(xtree::t_array<T_value, A_leaf, A_branch>& a0, std::vector<T_value>& a1, size_t a_i, T_iterator a_first, T_iterator a_last)
{
	a1.insert(a1.begin() + a_i, a_first, a_last);
	for (auto i = a0.f_at(a_i); a_first != a_last; ++a_first) {
		i = a0.f_insert(i, *a_first);
		assert(*i == *a_first);
		++i;
	}
	f_assert_equals(a0, a1);
}

template<typename T_value, size_t A_leaf, size_t A_branch, typename T>
void f_test_insert(xtree::t_array<T_value, A_leaf, A_branch>& a0, std::vector<T_value>& a1, size_t a_i, const T& a_values)
{
	f_test_insert(a0, a1, a_i, a_values.begin(), a_values.end());
}

template<typename T_value, size_t A_leaf, size_t A_branch>
void f_test_insert(xtree::t_array<T_value, A_leaf, A_branch>& a0, std::vector<T_value>& a1, size_t a_i, std::initializer_list<T_value> a_values)
{
	f_test_insert(a0, a1, a_i, a_values.begin(), a_values.end());
}

template<typename T_value, size_t A_leaf, size_t A_branch>
void f_test_erase(xtree::t_array<T_value, A_leaf, A_branch>& a0, std::vector<T_value>& a1, size_t a_i, size_t a_n)
{
	a1.erase(a1.begin() + a_i, a1.begin() + a_i + a_n);
	auto i = a0.f_at(a_i);
	for (size_t j = 0; j < a_n; ++j) {
		i = a0.f_erase(i);
		assert(i == a0.f_at(a_i));
	}
	f_assert_equals(a0, a1);
}