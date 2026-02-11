dict_table_copy_types(

	dtuple_t*		tuple,
	const dict_table_t*	table)
{
	ulint		i;

	for (i = 0; i < dtuple_get_n_fields(tuple); i++) {

		dfield_t*	dfield	= dtuple_get_nth_field(tuple, i);
		dtype_t*	dtype	= dfield_get_type(dfield);

		dfield_set_null(dfield);
		dict_col_copy_type(dict_table_get_nth_col(table, i), dtype);
	}
}
