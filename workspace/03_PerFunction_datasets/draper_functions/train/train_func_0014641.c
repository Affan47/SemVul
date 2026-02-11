gretl_vector_mean (const gretl_vector *v)
{
    double num = 0.0;
    int i, n, den = 0;

    if (gretl_is_null_matrix(v)) {
	return NADBL;
    }

    n = gretl_vector_get_length(v);
    if (n == 0) {
	return NADBL;
    }

    for (i=0; i<n; i++) {
	if (!na(v->val[i])) {
	    num += v->val[i];
	    den++;
	}
    }

    return (den > 0)? (num / den) : NADBL;
}
