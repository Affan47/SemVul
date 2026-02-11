dns_cache_flush(dns_cache_t *cache) {
	dns_db_t *db = NULL;
	isc_result_t result;

	result = cache_create_db(cache, &db);
	if (result != ISC_R_SUCCESS)
		return (result);

	LOCK(&cache->lock);
	LOCK(&cache->cleaner.lock);
	if (cache->cleaner.state == cleaner_s_idle) {
		if (cache->cleaner.iterator != NULL)
			dns_dbiterator_destroy(&cache->cleaner.iterator);
		(void) dns_db_createiterator(db, ISC_FALSE,
					     &cache->cleaner.iterator);
	} else {
		if (cache->cleaner.state == cleaner_s_busy)
			cache->cleaner.state = cleaner_s_done;
		cache->cleaner.replaceiterator = ISC_TRUE;
	}
	dns_db_detach(&cache->db);
	cache->db = db;
	UNLOCK(&cache->cleaner.lock);
	UNLOCK(&cache->lock);

	return (ISC_R_SUCCESS);
}
