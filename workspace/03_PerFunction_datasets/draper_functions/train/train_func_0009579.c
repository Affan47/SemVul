isl_mat_sub_alloc6(isl_ctx *ctx, isl_int **row,
	unsigned first_row, unsigned n_row, unsigned first_col, unsigned n_col)
{
	int i;
	struct isl_mat *mat;

	mat = isl_alloc_type(ctx, struct isl_mat);
	if (!mat)
		return NULL;
	mat->row = isl_alloc_array(ctx, isl_int *, n_row);
	if (n_row && !mat->row)
		goto error;
	for (i = 0; i < n_row; ++i)
		mat->row[i] = row[first_row+i] + first_col;
	mat->ctx = ctx;
	isl_ctx_ref(ctx);
	mat->ref = 1;
	mat->n_row = n_row;
	mat->n_col = n_col;
	mat->block = isl_blk_empty();
	mat->flags = ISL_MAT_BORROWED;
	return mat;
error:
	free(mat);
	return NULL;
}
