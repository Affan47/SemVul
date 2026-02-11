huge_ralloc(void *ptr, size_t oldsize, size_t size, size_t extra,
    size_t alignment, bool zero, bool try_tcache_dalloc)
{
	void *ret;
	size_t copysize;


	ret = huge_ralloc_no_move(ptr, oldsize, size, extra);
	if (ret != NULL)
		return (ret);


	if (alignment > chunksize)
		ret = huge_palloc(size + extra, alignment, zero);
	else
		ret = huge_malloc(size + extra, zero);

	if (ret == NULL) {
		if (extra == 0)
			return (NULL);

		if (alignment > chunksize)
			ret = huge_palloc(size, alignment, zero);
		else
			ret = huge_malloc(size, zero);

		if (ret == NULL)
			return (NULL);
	}


	copysize = (size < oldsize) ? size : oldsize;

#ifdef JEMALLOC_MREMAP


	if (oldsize >= chunksize && (config_dss == false || (chunk_in_dss(ptr)
	    == false && chunk_in_dss(ret) == false))) {
		size_t newsize = huge_salloc(ret);


		huge_dalloc(ptr, false);
		if (mremap(ptr, oldsize, newsize, MREMAP_MAYMOVE|MREMAP_FIXED,
		    ret) == MAP_FAILED) {


			char buf[BUFERROR_BUF];

			buferror(buf, sizeof(buf));
			malloc_printf("<jemalloc>: Error in mremap(): %s\n",
			    buf);
			if (opt_abort)
				abort();
			memcpy(ret, ptr, copysize);
			chunk_dealloc_mmap(ptr, oldsize);
		}
	} else
#endif
	{
		memcpy(ret, ptr, copysize);
		iqallocx(ptr, try_tcache_dalloc);
	}
	return (ret);
}
