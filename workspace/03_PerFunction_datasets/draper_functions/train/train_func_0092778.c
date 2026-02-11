test_core_vector__5(void)
{
	git_vector x;
	int i;

	git_vector_init(&x, 1, &compare_structs);

	for (i = 0; i < 10; i += 2)
		git_vector_insert_sorted(&x, alloc_struct(i), &merge_structs);

	for (i = 9; i > 0; i -= 2)
		git_vector_insert_sorted(&x, alloc_struct(i), &merge_structs);

	cl_assert(x.length == 10);
	cl_assert(_struct_count == 10);

	for (i = 0; i < 10; i += 2)
		git_vector_insert_sorted(&x, alloc_struct(i), &merge_structs);

	for (i = 9; i > 0; i -= 2)
		git_vector_insert_sorted(&x, alloc_struct(i), &merge_structs);

	cl_assert(x.length == 10);
	cl_assert(_struct_count == 10);

	for (i = 0; i < 10; ++i) {
		cl_assert(((my_struct *)git_vector_get(&x, i))->content == i);
		git__free(git_vector_get(&x, i));
		_struct_count--;
	}

	git_vector_free(&x);
}
