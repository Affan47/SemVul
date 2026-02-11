row_merge_drop_table(

	trx_t*		trx,
	dict_table_t*	table)
{

	ut_a(table->n_mysql_handles_opened == 0);

	return(row_drop_table_for_mysql(table->name, trx, FALSE));
}
