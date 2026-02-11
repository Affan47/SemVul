isl_vec_alloc(struct isl_ctx *ctx, unsigned size)
{
	struct isl_vec *vec;

	vec = isl_alloc_type(ctx, struct isl_vec);
	if (!vec)
		return NULL;

	vec->block = isl_blk_alloc(ctx, size);
	if (isl_blk_is_error(vec->block))
		goto error;

	vec->ctx = ctx;
	isl_ctx_ref(ctx);
	vec->ref = 1;
	vec->size = size;
	vec->el = vec->block.data;

	return vec;
error:
	isl_blk_free(ctx, vec->block);
	return NULL;
}
