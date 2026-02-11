gretl_matrix_copy_values_shaped (gretl_matrix *targ,
				     const gretl_matrix *src)
{
    int n = targ->rows * targ->cols;

    if (src->rows * src->cols != n) {
	fprintf(stderr, "gretl_matrix_copy_values_shaped: targ is %d x %d but src is %d x %d\n",
		targ->rows, targ->cols, src->rows, src->cols);
	return E_NONCONF;
    }

    if (n > 0) {
	memcpy(targ->val, src->val, n * sizeof *targ->val);
    }

    return 0;
}
