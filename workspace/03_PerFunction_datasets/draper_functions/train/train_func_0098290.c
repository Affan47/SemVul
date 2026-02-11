chunk_boot(void)
{


	chunksize = (ZU(1) << opt_lg_chunk);
	assert(chunksize >= PAGE);
	chunksize_mask = chunksize - 1;
	chunk_npages = (chunksize >> LG_PAGE);

	if (config_stats || config_prof) {
		if (malloc_mutex_init(&chunks_mtx))
			return (true);
		memset(&stats_chunks, 0, sizeof(chunk_stats_t));
	}
	if (config_dss && chunk_dss_boot())
		return (true);
	extent_tree_szad_new(&chunks_szad);
	extent_tree_ad_new(&chunks_ad);
	if (config_ivsalloc) {
		chunks_rtree = rtree_new((ZU(1) << (LG_SIZEOF_PTR+3)) -
		    opt_lg_chunk);
		if (chunks_rtree == NULL)
			return (true);
	}

	return (false);
}
