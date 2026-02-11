init_comp_ctx(struct comp_ctx **comp_ctx)
{
#ifdef USE_ZLIB
	z_stream *strm;

	if (global.maxzlibmem > 0 && (global.maxzlibmem - zlib_used_memory) < sizeof(struct comp_ctx))
		return -1;
#endif

	if (unlikely(pool_comp_ctx == NULL))
		pool_comp_ctx = create_pool("comp_ctx", sizeof(struct comp_ctx), MEM_F_SHARED);

	*comp_ctx = pool_alloc2(pool_comp_ctx);
	if (*comp_ctx == NULL)
		return -1;
#ifdef USE_ZLIB
	zlib_used_memory += sizeof(struct comp_ctx);

	strm = &(*comp_ctx)->strm;
	strm->zalloc = alloc_zlib;
	strm->zfree = free_zlib;
	strm->opaque = *comp_ctx;
#endif
	return 0;
}
