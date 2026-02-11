tcache_bin_flush_large(tcache_bin_t *tbin, size_t binind, unsigned rem
#if (defined(JEMALLOC_STATS) || defined(JEMALLOC_PROF))
    , tcache_t *tcache
#endif
    )
{
	void *ptr;
	unsigned i, nflush, ndeferred;
#ifdef JEMALLOC_STATS
	bool merged_stats = false;
#endif

	assert(binind < nhbins);
	assert(rem <= tbin->ncached);

	for (nflush = tbin->ncached - rem; nflush > 0; nflush = ndeferred) {

		arena_chunk_t *chunk = (arena_chunk_t *)CHUNK_ADDR2BASE(
		    tbin->avail[0]);
		arena_t *arena = chunk->arena;

		malloc_mutex_lock(&arena->lock);
#if (defined(JEMALLOC_PROF) || defined(JEMALLOC_STATS))
		if (arena == tcache->arena) {
#endif
#ifdef JEMALLOC_PROF
			arena_prof_accum(arena, tcache->prof_accumbytes);
			tcache->prof_accumbytes = 0;
#endif
#ifdef JEMALLOC_STATS
			merged_stats = true;
			arena->stats.nrequests_large += tbin->tstats.nrequests;
			arena->stats.lstats[binind - nbins].nrequests +=
			    tbin->tstats.nrequests;
			tbin->tstats.nrequests = 0;
#endif
#if (defined(JEMALLOC_PROF) || defined(JEMALLOC_STATS))
		}
#endif
		ndeferred = 0;
		for (i = 0; i < nflush; i++) {
			ptr = tbin->avail[i];
			assert(ptr != NULL);
			chunk = (arena_chunk_t *)CHUNK_ADDR2BASE(ptr);
			if (chunk->arena == arena)
				arena_dalloc_large(arena, chunk, ptr);
			else {


				tbin->avail[ndeferred] = ptr;
				ndeferred++;
			}
		}
		malloc_mutex_unlock(&arena->lock);
	}
#ifdef JEMALLOC_STATS
	if (merged_stats == false) {


		arena_t *arena = tcache->arena;
		malloc_mutex_lock(&arena->lock);
		arena->stats.nrequests_large += tbin->tstats.nrequests;
		arena->stats.lstats[binind - nbins].nrequests +=
		    tbin->tstats.nrequests;
		tbin->tstats.nrequests = 0;
		malloc_mutex_unlock(&arena->lock);
	}
#endif

	memmove(tbin->avail, &tbin->avail[tbin->ncached - rem],
	    rem * sizeof(void *));
	tbin->ncached = rem;
	if ((int)tbin->ncached < tbin->low_water)
		tbin->low_water = tbin->ncached;
}
