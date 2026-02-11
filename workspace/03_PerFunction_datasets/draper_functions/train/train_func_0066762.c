gretl_dataset_from_matrix (const gretl_matrix *m,
				    const int *list,
				    gretlopt opt,
				    int *err)
{
    DATASET *dset = NULL;
    const char **names;
    double x;
    int i, t, col, nv, T;

    if (gretl_is_null_matrix(m)) {
	*err = E_DATA;
	return NULL;
    }

    T = gretl_matrix_rows(m);
    nv = gretl_matrix_cols(m);

    if (list != NULL) {
	for (i=1; i<=list[0]; i++) {
	    col = list[i];
	    if (col < 1 || col > nv) {
		gretl_errmsg_sprintf("Variable number %d is out of bounds", col);
		*err = E_DATA;
		break;
	    } else if (opt & OPT_B) {

		for (t=0; t<T; t++) {
		    x = gretl_matrix_get(m, t, col-1);
		    if (xna(x)) {
			opt = OPT_NONE;
			break;
		    }
		}
	    }
	}
	nv = list[0];
    } else if (opt & OPT_B) {
	int N = T * nv;

	for (i=0; i<N; i++) {
	    if (xna(m->val[i])) {
		opt = OPT_NONE;
		break;
	    }
	}
    }

    if (!*err) {
	dset = create_auxiliary_dataset(nv + 1, T, opt);
	if (dset == NULL) {
	    *err = E_ALLOC;
	}
    }

    if (*err) {
	return NULL;
    }

    names = gretl_matrix_get_colnames(m);

    for (i=1; i<=nv; i++) {
	col = (list != NULL)? list[i] - 1 : i - 1;
	if (opt & OPT_B) {
	    dset->Z[i] = m->val + T * col;
	} else {
	    for (t=0; t<T; t++) {
		x = gretl_matrix_get(m, t, col);
		if (xna(x)) {
		    x = NADBL;
		}
		dset->Z[i][t] = x;
	    }
	}
	if (names != NULL) {
	    strcpy(dset->varname[i], names[col]);
	} else if (opt & OPT_N) {
	    sprintf(dset->varname[i], "%d", col + 1);
	} else {
	    sprintf(dset->varname[i], "col%d", col + 1);
	}
    }

    return dset;
}
