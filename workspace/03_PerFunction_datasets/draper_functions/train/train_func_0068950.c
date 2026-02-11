json_allows_caching(json_value *json) {
	long cache_ttl;
	int retval = 0;
	if (json_get_cache_ttl(json, &cache_ttl) == APR_SUCCESS) {
		retval = 1;
	}
	return retval;
}
