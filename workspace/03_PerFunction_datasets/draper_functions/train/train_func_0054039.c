arena_tcache_fill_small(arena_t *arena, tcache_bin_t *tbin, size_t binind,
    uint64_t prof_accumbytes)
{
	unsigned i, nfill;
	arena_bin_t *bin;
	arena_run_t *run;
	void *ptr;

	assert(tbin->ncached == 0);

	if (config_prof) {
		malloc_mutex_lock(&arena->lock);
		arena_prof_accum(arena, prof_accumbytes);
		malloc_mutex_unlock(&arena->lock);
	}
	bin = &arena->bins[binind];
	malloc_mutex_lock(&bin->lock);
	for (i = 0, nfill = (tcache_bin_info[binind].ncached_max >>
	    tbin->lg_fill_div); i < nfill; i++) {
		if ((run = bin->runcur) != NULL && run->nfree > 0)
			ptr = arena_run_reg_alloc(run, &arena_bin_info[binind]);
		else
			ptr = arena_bin_malloc_hard(arena, bin);
		if (ptr == NULL)
			break;
		if (config_fill && opt_junk) {
			arena_alloc_junk_small(ptr, &arena_bin_info[binind],
			    true);
		}

		tbin->avail[nfill - 1 - i] = ptr;
	}
	if (config_stats) {
		bin->stats.allocated += i * arena_bin_info[binind].reg_size;
		bin->stats.nmalloc += i;
		bin->stats.nrequests += tbin->tstats.nrequests;
		bin->stats.nfills++;
		tbin->tstats.nrequests = 0;
	}
	malloc_mutex_unlock(&bin->lock);
	tbin->ncached = i;
}
