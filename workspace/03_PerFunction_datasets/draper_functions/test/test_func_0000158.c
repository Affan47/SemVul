buf_pool_set_sizes(void)

{
	ulint	i;
	ulint	curr_size = 0;

	buf_pool_mutex_enter_all();

	for (i = 0; i < srv_buf_pool_instances; i++) {
		buf_pool_t*	buf_pool;

		buf_pool = buf_pool_from_array(i);
		curr_size += buf_pool->curr_pool_size;
	}

	srv_buf_pool_curr_size = curr_size;
	srv_buf_pool_old_size = srv_buf_pool_size;

	buf_pool_mutex_exit_all();
}
