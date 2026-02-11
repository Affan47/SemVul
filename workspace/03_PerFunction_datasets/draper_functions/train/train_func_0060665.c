allocate_johansen_extra_matrices (GRETL_VAR *v)
{
    if (v->jinfo->R0 != NULL &&
	v->jinfo->S00 != NULL &&
	v->jinfo->YY != NULL) {
	return 0;
    } else {
	int p0 = v->neqns;
	int p1 = p0 + n_restricted_terms(v);
	int p = p0 + p1;

	clear_gretl_matrix_err();

	if (v->jinfo->R0 == NULL) {
	    v->jinfo->R0 = gretl_matrix_alloc(v->T, p0);
	    v->jinfo->R1 = gretl_matrix_alloc(v->T, p1);
	}

	if (v->jinfo->S00 == NULL) {
	    v->jinfo->S00 = gretl_matrix_alloc(p0, p0);
	    v->jinfo->S11 = gretl_matrix_alloc(p1, p1);
	    v->jinfo->S01 = gretl_matrix_alloc(p0, p1);
	}

	if (v->ncoeff > 0 && v->jinfo->YY == NULL) {
	    v->jinfo->YY = gretl_matrix_alloc(v->T, p);
	    v->jinfo->RR = gretl_matrix_alloc(v->T, p);
	    v->jinfo->BB = gretl_matrix_alloc(v->X->cols, p);
	}

	return get_gretl_matrix_err();
    }
}
