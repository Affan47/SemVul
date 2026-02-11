equation_system_append_multi (equation_system *sys,
				  const char *param,
				  const DATASET *dset)
{
    char name1[VNAMELEN], name2[VNAMELEN];
    char fmt[12];
    int n, err = 0;

    if (sys == NULL) {
	gretl_errmsg_set(_(nosystem));
	return E_DATA;
    }

    sprintf(fmt, "%%%ds %%%ds", VNAMELEN-1, VNAMELEN-1);
    n = sscanf(param, fmt, name1, name2);

    if (n == 2) {

	const int *LY = get_list_by_name(name1);
	const int *LX = get_list_by_name(name2);

	if (LY == NULL || LX == NULL) {
	    err = E_DATA;
	} else {
	    err = add_equations_from_lists(sys, LY, LX, dset);
	}
    } else if (n == 1) {

	const gretl_matrix *m = get_matrix_by_name(name1);

	if (m == NULL) {
	    err = E_UNKVAR;
	} else if (m->rows == 0 || m->cols == 0) {
	    err = E_DATA;
	} else {
	    err = add_equations_from_matrix(sys, m, dset);
	}
    } else {
	err = E_DATA;
    }

    if (err) {
	equation_system_destroy(sys);
    }

    return err;
}
