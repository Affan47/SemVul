trx_i_s_cache_get_nth_row(

	trx_i_s_cache_t*	cache,
	enum i_s_table		table,
	ulint			n)
{
	i_s_table_cache_t*	table_cache;
	ulint			i;
	void*			row;

	table_cache = cache_select_table(cache, table);

	ut_a(n < table_cache->rows_used);

	row = NULL;

	for (i = 0; i < MEM_CHUNKS_IN_TABLE_CACHE; i++) {

		if (table_cache->chunks[i].offset
		    + table_cache->chunks[i].rows_allocd > n) {

			row = (char*) table_cache->chunks[i].base
				+ (n - table_cache->chunks[i].offset)
				* table_cache->row_size;
			break;
		}
	}

	ut_a(row != NULL);

	return(row);
}
