stratum_works(struct pool *pool)
{
	applog(LOG_INFO, "Testing pool %d stratum %s", pool->pool_no, pool->stratum_url);
	if (!extract_sockaddr(pool, pool->stratum_url))
		return false;

	if (!initiate_stratum(pool))
		return false;

	return true;
}
