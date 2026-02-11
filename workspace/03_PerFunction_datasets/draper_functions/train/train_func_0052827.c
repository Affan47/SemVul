ifree(void *ptr)
{
	size_t usize;
	UNUSED size_t rzsize JEMALLOC_CC_SILENCE_INIT(0);

	assert(ptr != NULL);
	assert(malloc_initialized || IS_INITIALIZER);

	if (config_prof && opt_prof) {
		usize = isalloc(ptr, config_prof);
		prof_free(ptr, usize);
	} else if (config_stats || config_valgrind)
		usize = isalloc(ptr, config_prof);
	if (config_stats)
		thread_allocated_tsd_get()->deallocated += usize;
	if (config_valgrind && opt_valgrind)
		rzsize = p2rz(ptr);
	iqalloc(ptr);
	JEMALLOC_VALGRIND_FREE(ptr, rzsize);
}
