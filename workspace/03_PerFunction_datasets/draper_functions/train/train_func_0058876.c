hash_cache_lookup(struct hash_cache *cache, const char *key)
{
	struct entry *e;
	void *result;

	e = hash_table_lookup(cache->table, key);
	if(e) {
		result = e->value;
		if(e->expires < time(0)) {
			result = hash_cache_remove(cache, key);
			if(result) cache->cleanup(result);
			result = 0;
		}
	} else {
		result = 0;
	}

	return result;
}
