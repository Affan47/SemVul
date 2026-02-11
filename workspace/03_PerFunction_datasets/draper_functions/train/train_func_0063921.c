import_csv (const char *fname, DATASET *dset,
		gretlopt opt, PRN *prn)
{
    const char *cols = NULL;
    const char *rows = NULL;
    int ci, err;

    err = incompatible_options(opt, OPT_F | OPT_L);
    if (err) {

	return err;
    }

    ci = (dset != NULL && dset->v > 0)? APPEND : OPEN;

    if (opt & OPT_F) {

	cols = get_optval_string(ci, OPT_F);
	if (cols == NULL || *cols == '\0') {
	    return E_PARSE;
	}
    } else if (opt & OPT_L) {

	cols = get_optval_string(ci, OPT_L);
	if (cols == NULL || *cols == '\0') {
	    return E_PARSE;
	}
    }

    if (opt & OPT_M) {

	rows = get_optval_string(ci, OPT_M);
	if (rows == NULL || *rows == '\0') {
	    return E_PARSE;
	}
    }

    return real_import_csv(fname, dset, cols, rows,
			   NULL, opt, prn);
}
