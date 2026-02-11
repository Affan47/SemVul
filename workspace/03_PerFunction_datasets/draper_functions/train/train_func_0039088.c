buf_pool_invalidate_instance(

	buf_pool_t*	buf_pool)
{
	ibool		freed;
	enum buf_flush	i;

	buf_pool_mutex_enter(buf_pool);

	for (i = BUF_FLUSH_LRU; i < BUF_FLUSH_N_TYPES; i++) {


		ut_ad(buf_pool->init_flush[i] == FALSE);


		if (buf_pool->n_flush[i] > 0) {
			buf_pool_mutex_exit(buf_pool);
			buf_flush_wait_batch_end(buf_pool, i);
			buf_pool_mutex_enter(buf_pool);
		}
	}

	buf_pool_mutex_exit(buf_pool);

	ut_ad(buf_all_freed_instance(buf_pool));

	freed = TRUE;

	while (freed) {
		freed = buf_LRU_search_and_free_block(buf_pool, 100);
	}

	buf_pool_mutex_enter(buf_pool);

	ut_ad(UT_LIST_GET_LEN(buf_pool->LRU) == 0);
	ut_ad(UT_LIST_GET_LEN(buf_pool->unzip_LRU) == 0);

	buf_pool->freed_page_clock = 0;
	buf_pool->LRU_old = NULL;
	buf_pool->LRU_old_len = 0;
	buf_pool->LRU_flush_ended = 0;

	memset(&buf_pool->stat, 0x00, sizeof(buf_pool->stat));
	buf_refresh_io_stats(buf_pool);

	buf_pool_mutex_exit(buf_pool);
}
