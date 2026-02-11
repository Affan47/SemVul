row_merge_drop_indexes(

	trx_t*		trx,
	dict_table_t*	table,
	dict_index_t**	index,
	ulint		num_created)
{
	ulint	key_num;

	for (key_num = 0; key_num < num_created; key_num++) {
		row_merge_drop_index(index[key_num], table, trx);
	}
}
