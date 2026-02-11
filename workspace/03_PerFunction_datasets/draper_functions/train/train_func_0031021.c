cleanup(void *data)
{
	struct name_cache *cache = (struct name_cache *)data;
	size_t i;

	if (cache != NULL) {
		for (i = 0; i < cache->size; i++) {
			if (cache->cache[i].name != NULL &&
			    cache->cache[i].name != NO_NAME)
				free((void *)(uintptr_t)cache->cache[i].name);
		}
		free(cache->buff);
		free(cache);
	}
}
