chunk_alloc(size_t size, bool zero)
{
	void *ret;

	(void)zero;
	assert(size != 0);
	assert((size & chunksize_mask) == 0);

#ifdef MALLOC_DSS
	if (opt_dss) {
		ret = chunk_recycle_dss(size, zero);
		if (ret != NULL) {
			goto RETURN;
		}

		ret = chunk_alloc_dss(size);
		if (ret != NULL)
			goto RETURN;
	}

	if (opt_mmap)
#endif
	{
		ret = chunk_alloc_mmap(size);
		if (ret != NULL)
			goto RETURN;
	}


	ret = NULL;
RETURN:
#ifdef MALLOC_STATS
	if (ret != NULL) {
		stats_chunks.nchunks += (size / chunksize);
		stats_chunks.curchunks += (size / chunksize);
	}
	if (stats_chunks.curchunks > stats_chunks.highchunks)
		stats_chunks.highchunks = stats_chunks.curchunks;
#endif

	assert(CHUNK_ADDR2BASE(ret) == ret);
	return (ret);
}
