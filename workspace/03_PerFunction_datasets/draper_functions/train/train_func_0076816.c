nlspec_add_param_names (nlspec *spec, const char *s)
{
    char sname[VNAMELEN];
    int n, err = 0;

    s += strspn(s, " ");
    n = gretl_namechar_spn(s);

    if (n == 0 || n >= VNAMELEN) {
	err = E_PARSE;
    } else {
	*sname = '\0';
	strncat(sname, s, n);
	if (!is_user_string(sname)) {
	    err = E_UNKVAR;
	} else {
	    const char *names = get_string_by_name(sname);

	    if (names == NULL || *names == '\0') {
		err = E_DATA;
	    } else {
		free(spec->parnames);
		spec->parnames = gretl_strdup(names);
		if (spec->parnames == NULL) {
		    err = E_ALLOC;
		}
	    }
	}
    }

    return err;
}
