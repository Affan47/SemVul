pool_alloc(Pool *pool, size_t size)
{
	void *addr;
	int err;

	if (!pool)
		return set_errnull(EINVAL);

	if ((err = pool_lock(pool)))
		return set_errnull(err);

	if (pool->used + size > pool->size)
	{
		pool_unlock(pool);
		return set_errnull(ENOSPC);
	}

	addr = pool->pool + pool->used;
	pool->used += size;

	if ((err = pool_unlock(pool)))
		return set_errnull(err);

	return addr;
}
