test_core_strmap__3(void)
{
	int i;
	char *str;
	git_strmap *table = git_strmap_alloc();
	cl_assert(table != NULL);

	insert_strings(table, 10000);

	i = 0;
	git_strmap_foreach_value(table, str, { i++; free(str); });
	cl_assert(i == 10000);

	git_strmap_free(table);
}
