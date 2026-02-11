prepare_kswapd_sleep(pg_data_t *pgdat, int order, long remaining,
					int classzone_idx)
{

	if (remaining)
		return false;


	if (waitqueue_active(&pgdat->pfmemalloc_wait))
		wake_up_all(&pgdat->pfmemalloc_wait);

	return pgdat_balanced(pgdat, order, classzone_idx);
}
