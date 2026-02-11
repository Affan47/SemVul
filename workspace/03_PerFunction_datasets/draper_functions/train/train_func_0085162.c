valid_long_opt (int ci, const char *s, OptStatus *status)
{
    gretlopt opt = OPT_NONE;
    int i;

    *status = 0;

    if (*s == '\0') {
	return 0;
    }

    if (vcv_opt_ok(ci) && !strcmp(s, "vcv")) {
	return OPT_O;
    }

    if (quiet_opt_ok(ci) && !strcmp(s, "quiet")) {
	return OPT_Q;
    }


    for (i=0; gretl_opts[i].o != 0; i++) {
	if (ci == gretl_opts[i].ci &&
	    !strcmp(s, gretl_opts[i].longopt)) {
	    opt = gretl_opts[i].o;
	    *status = gretl_opts[i].parminfo;
	    break;
	}
    }


    if (opt == OPT_NONE) {
	int optlen, slen = strlen(s);
	int nmatch = 0;

	for (i=0; gretl_opts[i].o != 0; i++) {
	    if (ci == gretl_opts[i].ci) {
		optlen = strlen(gretl_opts[i].longopt);
		if (optlen > slen && !strncmp(s, gretl_opts[i].longopt, slen)) {
		    opt = gretl_opts[i].o;
		    *status = gretl_opts[i].parminfo;
		    nmatch++;
		}
	    }
	}
	if (nmatch > 1) {
	    if (ci == SETOBS && !strcmp(s, "panel")) {

		return OPT_P;
	    }
	    *status = OPT_AMBIGUOUS;
	    return OPT_NONE;
	}
    }


    if (opt == OPT_NONE && !strcmp(s, "wald")) {
	opt = OPT_W;
	*status = 0;
    }

    return opt;
}
