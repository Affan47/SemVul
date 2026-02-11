arena_malloc_small(arena_t *arena, size_t size, bool zero)
{
	void *ret;
	arena_bin_t *bin;
	arena_run_t *run;
	size_t binind;

	binind = SMALL_SIZE2BIN(size);
	assert(binind < NBINS);
	bin = &arena->bins[binind];
	size = arena_bin_info[binind].reg_size;

	malloc_mutex_lock(&bin->lock);
	if ((run = bin->runcur) != NULL && run->nfree > 0)
		ret = arena_run_reg_alloc(run, &arena_bin_info[binind]);
	else
		ret = arena_bin_malloc_hard(arena, bin);

	if (ret == NULL) {
		malloc_mutex_unlock(&bin->lock);
		return (NULL);
	}

	if (config_stats) {
		bin->stats.allocated += size;
		bin->stats.nmalloc++;
		bin->stats.nrequests++;
	}
	malloc_mutex_unlock(&bin->lock);
	if (config_prof && isthreaded == false) {
		malloc_mutex_lock(&arena->lock);
		arena_prof_accum(arena, size);
		malloc_mutex_unlock(&arena->lock);
	}

	if (zero == false) {
		if (config_fill) {
			if (opt_junk) {
				arena_alloc_junk_small(ret,
				    &arena_bin_info[binind], false);
			} else if (opt_zero)
				memset(ret, 0, size);
		}
	} else {
		if (config_fill && opt_junk) {
			arena_alloc_junk_small(ret, &arena_bin_info[binind],
			    true);
		}
		VALGRIND_MAKE_MEM_UNDEFINED(ret, size);
		memset(ret, 0, size);
	}

	return (ret);
}
