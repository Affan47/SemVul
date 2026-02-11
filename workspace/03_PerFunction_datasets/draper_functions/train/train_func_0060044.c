isl_mat_is_equal(__isl_keep isl_mat *mat1, __isl_keep isl_mat *mat2)
{
	int i;

	if (!mat1 || !mat2)
		return -1;

	if (mat1->n_row != mat2->n_row)
		return 0;

	if (mat1->n_col != mat2->n_col)
		return 0;

	for (i = 0; i < mat1->n_row; ++i)
		if (!isl_seq_eq(mat1->row[i], mat2->row[i], mat1->n_col))
			return 0;

	return 1;
}
