release_map_cache(struct map_cache *cache)
{
	if (cache->ref_count <= 0) {
		err_printf("release_map_cache: suspicious cache has ref_count of 0\n");
	}
	if (cache->ref_count == 1) {
		if (cache->dat)
			free(cache->dat);
		free(cache);
		return;
	}
	cache->ref_count--;
}
