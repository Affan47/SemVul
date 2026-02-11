__pool_inc(struct pool *pool)
{
	BUG_ON(!mutex_is_locked(&dm_thin_pool_table.mutex));
	pool->ref_count++;
}
