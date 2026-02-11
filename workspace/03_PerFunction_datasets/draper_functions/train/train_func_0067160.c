dict_table_get_col_name(

	const dict_table_t*	table,
	ulint			col_nr)
{
	ulint		i;
	const char*	s;

	ut_ad(table);
	ut_ad(col_nr < table->n_def);
	ut_ad(table->magic_n == DICT_TABLE_MAGIC_N);

	s = table->col_names;
	if (s) {
		for (i = 0; i < col_nr; i++) {
			s += strlen(s) + 1;
		}
	}

	return(s);
}
