tcache_boot(void)
{

	if (opt_tcache) {
		unsigned i;


		if (opt_lg_tcache_max < 0 || (1U <<
		    opt_lg_tcache_max) < small_maxclass)
			tcache_maxclass = small_maxclass;
		else if ((1U << opt_lg_tcache_max) > arena_maxclass)
			tcache_maxclass = arena_maxclass;
		else
			tcache_maxclass = (1U << opt_lg_tcache_max);

		nhbins = nbins + (tcache_maxclass >> PAGE_SHIFT);


		tcache_bin_info = (tcache_bin_info_t *)base_alloc(nhbins *
		    sizeof(tcache_bin_info_t));
		if (tcache_bin_info == NULL)
			return (true);
		stack_nelms = 0;
		for (i = 0; i < nbins; i++) {
			if ((arena_bin_info[i].nregs << 1) <=
			    TCACHE_NSLOTS_SMALL_MAX) {
				tcache_bin_info[i].ncached_max =
				    (arena_bin_info[i].nregs << 1);
			} else {
				tcache_bin_info[i].ncached_max =
				    TCACHE_NSLOTS_SMALL_MAX;
			}
			stack_nelms += tcache_bin_info[i].ncached_max;
		}
		for (; i < nhbins; i++) {
			tcache_bin_info[i].ncached_max = TCACHE_NSLOTS_LARGE;
			stack_nelms += tcache_bin_info[i].ncached_max;
		}


		if (opt_lg_tcache_gc_sweep >= 0) {
			tcache_gc_incr = ((1U << opt_lg_tcache_gc_sweep) /
			    nbins) + (((1U << opt_lg_tcache_gc_sweep) % nbins ==
			    0) ? 0 : 1);
		} else
			tcache_gc_incr = 0;

		if (pthread_key_create(&tcache_tsd, tcache_thread_cleanup) !=
		    0) {
			malloc_write(
			    "<jemalloc>: Error in pthread_key_create()\n");
			abort();
		}
	}

	return (false);
}
