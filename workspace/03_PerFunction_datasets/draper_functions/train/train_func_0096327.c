gretl_matrix_pergm (const gretl_matrix *x, int m,
					 int *err)
{
    gretl_matrix *p = NULL;
    gretl_matrix *f = NULL;

    f = gretl_matrix_fft(x, err);
    if (*err) {
	return NULL;
    }

    p = gretl_column_vector_alloc(m);

    if (p == NULL) {
	*err = E_ALLOC;
    } else {
	int T = gretl_vector_get_length(x);
	double re, im, scale = M_2PI * T;
	int i;

	for (i=0; i<m; i++) {
	    re = gretl_matrix_get(f, i+1, 0);
	    im = gretl_matrix_get(f, i+1, 1);
	    p->val[i] = (re*re + im*im) / scale;
	}
    }

    gretl_matrix_free(f);

    return p;
}
