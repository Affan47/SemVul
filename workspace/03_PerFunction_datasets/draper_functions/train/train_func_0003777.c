dict_table_get_highest_foreign_id(

	dict_table_t*	table)
{
	dict_foreign_t*	foreign;
	char*		endp;
	ulint		biggest_id	= 0;
	ulint		id;
	ulint		len;

	ut_a(table);

	len = ut_strlen(table->name);
	foreign = UT_LIST_GET_FIRST(table->foreign_list);

	while (foreign) {
		if (ut_strlen(foreign->id) > ((sizeof dict_ibfk) - 1) + len
		    && 0 == ut_memcmp(foreign->id, table->name, len)
		    && 0 == ut_memcmp(foreign->id + len,
				      dict_ibfk, (sizeof dict_ibfk) - 1)
		    && foreign->id[len + ((sizeof dict_ibfk) - 1)] != '0') {


			id = strtoul(foreign->id + len
				     + ((sizeof dict_ibfk) - 1),
				     &endp, 10);
			if (*endp == '\0') {
				ut_a(id != biggest_id);

				if (id > biggest_id) {
					biggest_id = id;
				}
			}
		}

		foreign = UT_LIST_GET_NEXT(foreign_list, foreign);
	}

	return(biggest_id);
}
