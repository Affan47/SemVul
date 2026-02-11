fetch_data_into_cache(

	trx_i_s_cache_t*	cache)
{
	trx_t*			trx;
	i_s_trx_row_t*		trx_row;
	i_s_locks_row_t*	requested_lock_row;

	ut_ad(mutex_own(&kernel_mutex));

	trx_i_s_cache_clear(cache);


	for (trx = UT_LIST_GET_FIRST(trx_sys->trx_list);
	     trx != NULL;
	     trx = UT_LIST_GET_NEXT(trx_list, trx)) {

		if (!add_trx_relevant_locks_to_cache(cache, trx,
						     &requested_lock_row)) {

			cache->is_truncated = TRUE;
			return;
		}

		trx_row = (i_s_trx_row_t*)
			table_cache_create_empty_row(&cache->innodb_trx,
						     cache);


		if (trx_row == NULL) {

			cache->is_truncated = TRUE;
			return;
		}

		if (!fill_trx_row(trx_row, trx, requested_lock_row, cache)) {


			cache->innodb_trx.rows_used--;
			cache->is_truncated = TRUE;
			return;
		}
	}

	cache->is_truncated = FALSE;
}
