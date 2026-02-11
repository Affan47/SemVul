manage_workers(struct worker *worker)
{
	struct worker_pool *pool = worker->pool;

	if (pool->flags & POOL_MANAGER_ACTIVE)
		return false;

	pool->flags |= POOL_MANAGER_ACTIVE;
	pool->manager = worker;

	maybe_create_worker(pool);

	pool->manager = NULL;
	pool->flags &= ~POOL_MANAGER_ACTIVE;
	wake_up(&wq_manager_wait);
	return true;
}
