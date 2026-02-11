chunk_alloc(size_t size, bool base, bool *zero)
{
	void *ret;

	assert(size != 0);
	assert((size & chunksize_mask) == 0);

#ifdef JEMALLOC_SWAP
	if (swap_enabled) {
		ret = chunk_alloc_swap(size, zero);
		if (ret != NULL)
			goto RETURN;
	}

	if (swap_enabled == false || opt_overcommit) {
#endif
#ifdef JEMALLOC_DSS
		ret = chunk_alloc_dss(size, zero);
		if (ret != NULL)
			goto RETURN;
#endif
		ret = chunk_alloc_mmap(size);
		if (ret != NULL) {
			*zero = true;
			goto RETURN;
		}
#ifdef JEMALLOC_SWAP
	}
#endif


	ret = NULL;
RETURN:
#ifdef JEMALLOC_IVSALLOC
	if (base == false && ret != NULL) {
		if (rtree_set(chunks_rtree, (uintptr_t)ret, ret)) {
			chunk_dealloc(ret, size, true);
			return (NULL);
		}
	}
#endif
#if (defined(JEMALLOC_STATS) || defined(JEMALLOC_PROF))
	if (ret != NULL) {
#  ifdef JEMALLOC_PROF
		bool gdump;
#  endif
		malloc_mutex_lock(&chunks_mtx);
#  ifdef JEMALLOC_STATS
		stats_chunks.nchunks += (size / chunksize);
#  endif
		stats_chunks.curchunks += (size / chunksize);
		if (stats_chunks.curchunks > stats_chunks.highchunks) {
			stats_chunks.highchunks = stats_chunks.curchunks;
#  ifdef JEMALLOC_PROF
			gdump = true;
#  endif
		}
#  ifdef JEMALLOC_PROF
		else
			gdump = false;
#  endif
		malloc_mutex_unlock(&chunks_mtx);
#  ifdef JEMALLOC_PROF
		if (opt_prof && opt_prof_gdump && gdump)
			prof_gdump();
#  endif
	}
#endif

	assert(CHUNK_ADDR2BASE(ret) == ret);
	return (ret);
}
