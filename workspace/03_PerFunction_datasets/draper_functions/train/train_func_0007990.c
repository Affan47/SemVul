isl_mat_dup(struct isl_mat *mat)
{
	int i;
	struct isl_mat *mat2;

	if (!mat)
		return NULL;
	mat2 = isl_mat_alloc(mat->ctx, mat->n_row, mat->n_col);
	if (!mat2)
		return NULL;
	for (i = 0; i < mat->n_row; ++i)
		isl_seq_cpy(mat2->row[i], mat->row[i], mat->n_col);
	return mat2;
}
