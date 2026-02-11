LWE_lambda (const gretl_matrix *I, int n)
{
    gretl_matrix *lambda;
    int i, m = gretl_vector_get_length(I);

    lambda = gretl_column_vector_alloc(m);

    if (lambda != NULL) {
	for (i=0; i<m; i++) {
	    gretl_vector_set(lambda, i, (M_2PI / n) * (i + 1));
	}
    }

    return lambda;
}
