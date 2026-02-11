stats_print_atexit(void)
{

	if (config_tcache && config_stats) {
		unsigned i;


		for (i = 0; i < narenas; i++) {
			arena_t *arena = arenas[i];
			if (arena != NULL) {
				tcache_t *tcache;


				malloc_mutex_lock(&arena->lock);
				ql_foreach(tcache, &arena->tcache_ql, link) {
					tcache_stats_merge(tcache, arena);
				}
				malloc_mutex_unlock(&arena->lock);
			}
		}
	}
	je_malloc_stats_print(NULL, NULL, NULL);
}
