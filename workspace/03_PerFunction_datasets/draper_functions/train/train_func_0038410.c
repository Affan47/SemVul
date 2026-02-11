buf_pool_init_instance(

	buf_pool_t*	buf_pool,
	ulint		buf_pool_size,
	ibool		populate,
	ulint		instance_no)
{
	ulint		i;
	buf_chunk_t*	chunk;


	mutex_create(buf_pool_mutex_key,
		     &buf_pool->mutex, SYNC_BUF_POOL);
	mutex_create(buf_pool_zip_mutex_key,
		     &buf_pool->zip_mutex, SYNC_BUF_BLOCK);

	buf_pool_mutex_enter(buf_pool);

	if (buf_pool_size > 0) {
		buf_pool->n_chunks = 1;
		buf_pool->chunks = chunk = mem_zalloc(sizeof *chunk);

		UT_LIST_INIT(buf_pool->free);

		if (!buf_chunk_init(buf_pool, chunk, buf_pool_size, populate)) {
			mem_free(chunk);
			mem_free(buf_pool);

			buf_pool_mutex_exit(buf_pool);

			return(DB_ERROR);
		}

		buf_pool->instance_no = instance_no;
		buf_pool->old_pool_size = buf_pool_size;
		buf_pool->curr_size = chunk->size;
		buf_pool->curr_pool_size = buf_pool->curr_size * UNIV_PAGE_SIZE;

		buf_pool->page_hash = hash_create(2 * buf_pool->curr_size);
		buf_pool->zip_hash = hash_create(2 * buf_pool->curr_size);

		buf_pool->last_printout_time = ut_time();
	}


	mutex_create(flush_list_mutex_key, &buf_pool->flush_list_mutex,
		     SYNC_BUF_FLUSH_LIST);

	for (i = BUF_FLUSH_LRU; i < BUF_FLUSH_N_TYPES; i++) {
		buf_pool->no_flush[i] = os_event_create(NULL);
	}


	buf_pool_mutex_exit(buf_pool);

	return(DB_SUCCESS);
}
