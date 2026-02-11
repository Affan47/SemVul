set_var_info (const char *line, gretlopt opt,
			 DATASET *dset)
{
    char *p, vname[VNAMELEN];
    int v, err = 0;

    if (dset == NULL || dset->varinfo == NULL) {
	return E_NODATA;
    }


    line += strcspn(line, " ");
    line += strspn(line, " ");

    if (gretl_scan_varname(line, vname) != 1) {
	return E_PARSE;
    }


    line += strcspn(line, " ");

    if (gretl_is_scalar(vname)) {
	v = gretl_scalar_get_value(vname, NULL);
	if (v < 0 || v >= dset->v) {
	    return E_UNKVAR;
	}
    } else if (integer_string(vname)) {
	v = atoi(vname);
	if (v < 0 || v >= dset->v) {
	    return E_UNKVAR;
	}
    } else {
	v = series_index(dset, vname);
	if (v < 0 || v >= dset->v) {
	    gretl_errmsg_sprintf(_("Unknown variable '%s'"), vname);
	    return E_UNKVAR;
	}
    }

    if (opt & OPT_D) {
	series_set_discrete(dset, v, 1);
    } else if (opt & OPT_C) {
	series_set_discrete(dset, v, 0);
    }

    if (opt & OPT_I) {
	const char *s = get_optval_string(SETINFO, OPT_I);

	if (s == NULL) {
	    err = E_ARGS;
	} else {
	    series_record_label(dset, v, s);
	}
    } else if (strstr(line, " -d ")) {

	p = get_flag_field(line, 'd');
	if (p != NULL) {
	    series_record_label(dset, v, p);
	    free(p);
	}
    }

    if (opt & OPT_G) {
	const char *s = get_optval_string(SETINFO, OPT_G);

	if (s == NULL) {
	    err = E_ARGS;
	} else {
	    series_record_display_name(dset, v, s);
	}
    } else if (strstr(line, " -n ")) {

	p = get_flag_field(line, 'n');
	if (p != NULL) {
	    series_record_display_name(dset, v, p);
	    free(p);
	}
    }

    return err;
}
