init_stratum_thread(struct pool *pool)
{
	if (unlikely(pthread_create(&pool->stratum_thread, NULL, stratum_thread, (void *)pool)))
		quit(1, "Failed to create stratum thread");
}
