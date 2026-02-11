jemalloc_prefork(void)
#else
JEMALLOC_EXPORT void
_malloc_prefork(void)
#endif
{
	unsigned i;

#ifdef JEMALLOC_MUTEX_INIT_CB
	if (malloc_initialized == false)
		return;
#endif
	assert(malloc_initialized);


	ctl_prefork();
	malloc_mutex_prefork(&arenas_lock);
	for (i = 0; i < narenas_total; i++) {
		if (arenas[i] != NULL)
			arena_prefork(arenas[i]);
	}
	prof_prefork();
	chunk_prefork();
	base_prefork();
	huge_prefork();
}
