scan_string (char *targ, const char **psrc, int width,
	     struct bracket_scan *bscan, int *ns)
{
    int n, err = 0;

    *psrc += strspn(*psrc, " \t\n");

    if (bscan->chrs != NULL) {
	if (bscan->reverse) {
	    n = strcspn(*psrc, bscan->chrs);
	} else {
	    n = strspn(*psrc, bscan->chrs);
	}
    } else {
	n = strcspn(*psrc, " \t\n");
    }

#if PSDEBUG
    fprintf(stderr, "scan_string: *psrc='%s', n=%d\n", *psrc, n);
    int m = strcspn(*psrc, "\n");
    fprintf(stderr, "m=%d (chrs='%s')\n", m, bscan->chrs);
#endif

    if (width != WIDTH_UNSPEC && n > width) {
	n = width;
    }

    if (targ != NULL) {
	user_var *uvar;

	uvar = get_user_var_of_type_by_name(targ, GRETL_TYPE_STRING);

	if (uvar == NULL) {
	    gretl_errmsg_sprintf(_("%s: not a string variable"), targ);
	    err = E_DATA;
	} else if (n > 0) {
	    char *conv = gretl_strndup(*psrc, n);

	    if (conv == NULL) {
		err = E_ALLOC;
	    } else {
		user_var_replace_value(uvar, conv);
		*psrc += n;
	    }
	    if (!err) {
		*ns += 1;
	    }
	}
    } else {
	*psrc += n;
    }

    return err;
}
