radeonCheckQuery(struct gl_context *ctx, struct gl_query_object *q)
{
	radeon_print(RADEON_STATE, RADEON_TRACE, "%s: query id %d\n", __FUNCTION__, q->Id);
\
#ifdef DRM_RADEON_GEM_BUSY
	radeonContextPtr radeon = RADEON_CONTEXT(ctx);

	struct radeon_query_object *query = (struct radeon_query_object *)q;
	uint32_t domain;


	if (radeon_bo_is_referenced_by_cs(query->bo, radeon->cmdbuf.cs)) {
		ctx->Driver.Flush(ctx);
	}

	if (radeon_bo_is_busy(query->bo, &domain) == 0) {
		radeonQueryGetResult(ctx, q);
		query->Base.Ready = GL_TRUE;
	}
#else
	radeonWaitQuery(ctx, q);
#endif
}
