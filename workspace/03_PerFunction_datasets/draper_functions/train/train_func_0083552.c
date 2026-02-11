buf_pool_check_num_pending_io(void)

{
	ulint		i;
	ulint		pending_io = 0;

	buf_pool_mutex_enter_all();

	for (i = 0; i < srv_buf_pool_instances; i++) {
		const buf_pool_t*	buf_pool;

		buf_pool = buf_pool_from_array(i);

		pending_io += buf_pool->n_pend_reads
			      + buf_pool->n_flush[BUF_FLUSH_LRU]
			      + buf_pool->n_flush[BUF_FLUSH_LIST]
			      + buf_pool->n_flush[BUF_FLUSH_SINGLE_PAGE];

	}

	buf_pool_mutex_exit_all();

	return(pending_io);
}
