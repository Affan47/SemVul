free_zlib(void *opaque, void *ptr)
{
	struct comp_ctx *ctx = opaque;
	struct pool_head *pool = NULL;

	if (ptr == ctx->zlib_window)
		pool = zlib_pool_window;
	else if (ptr == ctx->zlib_deflate_state)
		pool = zlib_pool_deflate_state;
	else if (ptr == ctx->zlib_prev)
		pool = zlib_pool_prev;
	else if (ptr == ctx->zlib_head)
		pool = zlib_pool_head;
	else if (ptr == ctx->zlib_pending_buf)
		pool = zlib_pool_pending_buf;

	pool_free2(pool, ptr);
	zlib_used_memory -= pool->size;
}
