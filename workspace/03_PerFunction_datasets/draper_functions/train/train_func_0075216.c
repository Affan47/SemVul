buf_get_total_list_len(

	ulint*		LRU_len,
	ulint*		free_len,
	ulint*		flush_list_len)
{
	ulint		i;

	*LRU_len = 0;
	*free_len = 0;
	*flush_list_len = 0;

	for (i = 0; i < srv_buf_pool_instances; i++) {
		buf_pool_t*	buf_pool;

		buf_pool = buf_pool_from_array(i);
		*LRU_len += UT_LIST_GET_LEN(buf_pool->LRU);
		*free_len += UT_LIST_GET_LEN(buf_pool->free);
		*flush_list_len += UT_LIST_GET_LEN(buf_pool->flush_list);
	}
}
