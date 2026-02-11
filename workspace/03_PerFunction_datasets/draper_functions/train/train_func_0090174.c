gnumeric_cholesky (GnmFuncEvalInfo *ei, GnmValue const * const *argv)
{
	GnmMatrix *A = NULL;
	GnmMatrix *B = NULL;
	GnmValue *res = NULL;

	A = gnm_matrix_from_value (argv[0], &res, ei->pos);
	if (!A) goto out;

	if (A->cols != A->rows || gnm_matrix_is_empty (A) || !symmetric (A)) {
		res = value_new_error_VALUE (ei->pos);
		goto out;
	}

	B = gnm_matrix_new (A->rows, A->cols);

	if (gnm_matrix_cholesky (A, B))
		res = gnm_matrix_to_value (B);
	else
		res = value_new_error_NUM (ei->pos);

out:
	if (A) gnm_matrix_free (A);
	if (B) gnm_matrix_free (B);
	return res;
}
