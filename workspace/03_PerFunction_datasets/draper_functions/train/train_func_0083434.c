je_dallocx(void *ptr, int flags)
{
	size_t usize;
	UNUSED size_t rzsize JEMALLOC_CC_SILENCE_INIT(0);
	unsigned arena_ind = ((unsigned)(flags >> 8)) - 1;
	bool try_tcache;

	assert(ptr != NULL);
	assert(malloc_initialized || IS_INITIALIZER);

	if (arena_ind != UINT_MAX) {
		arena_chunk_t *chunk = (arena_chunk_t *)CHUNK_ADDR2BASE(ptr);
		try_tcache = (chunk == ptr || chunk->arena !=
		    arenas[arena_ind]);
	} else
		try_tcache = true;

	UTRACE(ptr, 0, 0);
	if (config_stats || config_valgrind)
		usize = isalloc(ptr, config_prof);
	if (config_prof && opt_prof) {
		if (config_stats == false && config_valgrind == false)
			usize = isalloc(ptr, config_prof);
		prof_free(ptr, usize);
	}
	if (config_stats)
		thread_allocated_tsd_get()->deallocated += usize;
	if (config_valgrind && opt_valgrind)
		rzsize = p2rz(ptr);
	iqalloct(ptr, try_tcache);
	JEMALLOC_VALGRIND_FREE(ptr, rzsize);
}
