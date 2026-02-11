get_inner_key_id (const char *s, int n,
			     const DATASET *dset,
			     int *err)
{
    char vname[VNAMELEN];
    int id = -1;

    if (n == 0 || n >= VNAMELEN) {
	*err = E_PARSE;
    } else {
	*vname = '\0';
	strncat(vname, s, n);
	if (gretl_namechar_spn(vname) != n) {
	    gretl_errmsg_sprintf(_("field '%s' in command is invalid"), vname);
	    *err = E_PARSE;
	} else {
	    id = current_series_index(dset, vname);
	    if (id < 0) {
		*err = E_UNKVAR;
	    }
	}
    }

    return id;
}
