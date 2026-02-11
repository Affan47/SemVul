gretl_matrix_subtract_reversed (const gretl_matrix *a, gretl_matrix *b)
{
    int i, n;

    if (a->rows != b->rows || a->cols != b->cols) {
	return E_NONCONF;
    }

    n = a->rows * b->cols;

#if defined(_OPENMP)
    if (!libset_use_openmp(n)) {
	goto st_mode;
    }
#pragma omp parallel for private(i)
    for (i=0; i<n; i++) {
	b->val[i] = a->val[i] - b->val[i];
    }
    return 0;

 st_mode:
#endif

    for (i=0; i<n; i++) {
	b->val[i] = a->val[i] - b->val[i];
    }

    return 0;
}
