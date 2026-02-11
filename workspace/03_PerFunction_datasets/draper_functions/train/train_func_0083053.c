cache_free(git_pack_cache *cache)
{
	khiter_t k;

	if (cache->entries) {
		for (k = kh_begin(cache->entries); k != kh_end(cache->entries); k++) {
			if (kh_exist(cache->entries, k))
				free_cache_object(kh_value(cache->entries, k));
		}

		git_offmap_free(cache->entries);
		cache->entries = NULL;
	}
}
