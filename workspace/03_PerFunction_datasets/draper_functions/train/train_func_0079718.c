dict_index_copy(

	dict_index_t*		index1,
	dict_index_t*		index2,
	const dict_table_t*	table,
	ulint			start,
	ulint			end)
{
	dict_field_t*	field;
	ulint		i;


	for (i = start; i < end; i++) {

		field = dict_index_get_nth_field(index2, i);
		dict_index_add_col(index1, table, field->col,
				   field->prefix_len);
	}
}
