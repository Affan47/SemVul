dict_table_get_referenced_constraint(

	dict_table_t*	table,
	dict_index_t*	index)
{
	dict_foreign_t*	foreign;

	ut_ad(index != NULL);
	ut_ad(table != NULL);

	for (foreign = UT_LIST_GET_FIRST(table->referenced_list);
	     foreign;
	     foreign = UT_LIST_GET_NEXT(referenced_list, foreign)) {

		if (foreign->referenced_index == index) {

			return(foreign);
		}
	}

	return(NULL);
}
