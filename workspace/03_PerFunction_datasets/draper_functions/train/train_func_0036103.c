reorder_responses (const GRETL_VAR *var, int *err)
{
    gretl_matrix *S, *C;
    int i, j, r, c;
    double x;

    S = gretl_matrix_copy(var->S);
    C = gretl_matrix_copy(var->C);

    if (S == NULL || C == NULL) {
	gretl_matrix_free(S);
	gretl_matrix_free(C);
	*err = E_ALLOC;
	return NULL;
    }

    for (i=0; i<var->neqns; i++) {
	r = var->ord->val[i];
	for (j=0; j<var->neqns; j++) {
	    c = var->ord->val[j];
	    x = gretl_matrix_get(var->S, r, c);
	    gretl_matrix_set(S, i, j, x);
	}
    }

    gretl_matrix_cholesky_decomp(S);

    for (i=0; i<var->neqns; i++) {
	r = var->ord->val[i];
	for (j=0; j<var->neqns; j++) {
	    c = var->ord->val[j];
	    x = gretl_matrix_get(S, i, j);
	    gretl_matrix_set(C, r, c, x);
	}
    }

    gretl_matrix_free(S);

    return C;
}
