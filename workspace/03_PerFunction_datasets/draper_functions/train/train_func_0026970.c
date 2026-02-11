isl_mat_alloc(struct isl_ctx *ctx,
	unsigned n_row, unsigned n_col)
{
	int i;
	struct isl_mat *mat;

	mat = isl_alloc_type(ctx, struct isl_mat);
	if (!mat)
		return NULL;

	mat->row = NULL;
	mat->block = isl_blk_alloc(ctx, n_row * n_col);
	if (isl_blk_is_error(mat->block))
		goto error;
	mat->row = isl_alloc_array(ctx, isl_int *, n_row);
	if (n_row && !mat->row)
		goto error;

	for (i = 0; i < n_row; ++i)
		mat->row[i] = mat->block.data + i * n_col;

	mat->ctx = ctx;
	isl_ctx_ref(ctx);
	mat->ref = 1;
	mat->n_row = n_row;
	mat->n_col = n_col;
	mat->max_col = n_col;
	mat->flags = 0;

	return mat;
error:
	isl_blk_free(ctx, mat->block);
	free(mat);
	return NULL;
}
