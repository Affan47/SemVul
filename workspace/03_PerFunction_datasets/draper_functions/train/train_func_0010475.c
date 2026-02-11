isl_blk_extend(struct isl_ctx *ctx, struct isl_blk block,
				size_t new_n)
{
	if (isl_blk_is_empty(block))
		return isl_blk_alloc(ctx, new_n);

	return extend(ctx, block, new_n);
}
