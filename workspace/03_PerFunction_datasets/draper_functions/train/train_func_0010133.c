insert_strings(git_strmap *table, int count)
{
	int i, j, over, err;
	char *str;

	for (i = 0; i < count; ++i) {
		str = malloc(10);
		for (j = 0; j < 10; ++j)
			str[j] = 'a' + (i % 26);
		str[9] = '\0';


		for (j = 0, over = i / 26; over > 0; j++, over = over / 26)
			str[j] = 'A' + (over % 26);

		git_strmap_insert(table, str, str, err);
		cl_assert(err >= 0);
	}

	cl_assert((int)git_strmap_num_entries(table) == count);
}
