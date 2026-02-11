test_pool_thread(void *arg)
{
	struct pool *pool = (struct pool *)arg;

	if (!pool->blocking)
		pthread_detach(pthread_self());
retry:
	if (pool->removed)
		goto out;
	if (pool_active(pool, false)) {
		pool_tclear(pool, &pool->idle);
		bool first_pool = false;

		cg_wlock(&control_lock);
		if (!pools_active) {
			currentpool = pool;
			if (pool->pool_no != 0)
				first_pool = true;
			pools_active = true;
		}
		cg_wunlock(&control_lock);

		if (unlikely(first_pool))
			applog(LOG_NOTICE, "Switching to pool %d %s - first alive pool", pool->pool_no, pool->rpc_url);

		pool_resus(pool);
		switch_pools(NULL);
	} else {
		pool_died(pool);
		if (!pool->blocking) {
			sleep(5);
			goto retry;
		}
	}

	pool->testing = false;
out:
	return NULL;
}
