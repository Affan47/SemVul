slab_cache_alloc(slab_cache_t* cache)
{
	slab_t* slab = cache->slabs_free;
	if(!cache->slabs_free) {
		slab = slab_create(cache);
		if (slab == NULL) {
			return NULL;
		}
	}


	return slab_alloc(slab);
}
