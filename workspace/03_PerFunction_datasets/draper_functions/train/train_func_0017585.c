remove_pool(struct pool *pool)
{
	int i, last_pool = total_pools - 1;
	struct pool *other;


	for (i = 0; i < total_pools; i++) {
		other = pools[i];
		if (other->prio > pool->prio)
			other->prio--;
	}

	if (pool->pool_no < last_pool) {

		(pools[last_pool])->pool_no = pool->pool_no;
		pools[pool->pool_no] = pools[last_pool];
	}

	pool->pool_no = total_pools;
	pool->removed = true;
	total_pools--;
}
