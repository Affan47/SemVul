user_matrix_eigen_analysis (const gretl_matrix *m, const char *rname, int symm,
			    int *err)
{
    gretl_matrix *C = NULL;
    gretl_matrix *E = NULL;
    int vecs = 0;

    if (gretl_is_null_matrix(m)) {
	*err = E_DATA;
	return NULL;
    }

    if (gretl_matrix_xna_check(m)) {
	*err = E_NAN;
	return NULL;
    }

    if (!nullarg(rname)) {
	vecs = 1;
	if (get_matrix_by_name(rname) == NULL) {
	    gretl_errmsg_sprintf(_("'%s': no such matrix"), rname);
	    *err = E_UNKVAR;
	    return NULL;
	}
    }

    C = gretl_matrix_copy(m);
    if (C == NULL) {
	*err = E_ALLOC;
    }

    if (!*err) {
	if (symm) {
	    E = gretl_symmetric_matrix_eigenvals(C, vecs, err);
	} else {
	    E = gretl_general_matrix_eigenvals(C, vecs, err);
	    if (E != NULL && E->cols == 2) {
		maybe_eigen_trim(E);
	    }
	}
    }

    if (!*err && vecs) {
	user_matrix_replace_matrix_by_name(rname, C);
    }

    if (!vecs) {
	gretl_matrix_free(C);
    }

    return E;
}
