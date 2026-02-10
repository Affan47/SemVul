cache_evict_entries(git_cache *cache)
{
	uint32_t seed = rand();
	size_t evict_count = 8;
	ssize_t evicted_memory = 0;


	if (evict_count > kh_size(cache->map)) {
		clear_cache(cache);
		return;
	}

	while (evict_count > 0) {
		khiter_t pos = seed++ % kh_end(cache->map);

		if (kh_exist(cache->map, pos)) {
			git_cached_obj *evict = kh_val(cache->map, pos);

			evict_count--;
			evicted_memory += evict->size;
			git_cached_obj_decref(evict);

			kh_del(oid, cache->map, pos);
		}
	}

	cache->used_memory -= evicted_memory;
	git_atomic_ssize_add(&git_cache__current_storage, -evicted_memory);
}
