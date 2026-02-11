isl_mat_scale_down(__isl_take isl_mat *mat, isl_int m)
{
	int i;

	if (isl_int_is_one(m))
		return mat;

	mat = isl_mat_cow(mat);
	if (!mat)
		return NULL;

	for (i = 0; i < mat->n_row; ++i)
		isl_seq_scale_down(mat->row[i], mat->row[i], m, mat->n_col);

	return mat;
}
