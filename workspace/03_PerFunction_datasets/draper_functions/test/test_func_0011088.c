option_set(user, opt, admin, value)
    char *user, *opt;
    int admin;
    char *value;
{
    int globflag = 0, type = 0, result;
    long delta;
    char *scan, *newval, *oldval;
    char dbname[256];


    snprintf(dbname, sizeof(dbname), optiondb, user);


    if (admin) {

	if (*opt == '*') {
	    globflag = 1;
	    strcpy(dbname, options);
	    ++opt;
	}

	if (*opt == '%') {
	    ++type;
	    if (*++opt == '%') {
		++type, ++opt;
	    }
	}
    }

    for (scan = opt; *scan; ++scan) {
	if (*scan == '*' || *scan == '%') return (-1);
    }
    if (!strcasecmp(opt, opt_usage)) return (-1);


    if (sdb_writelock(dbname, opt, SDB_ICASE) < 0) return (-1);


    if (sdb_get(dbname, opt, SDB_ICASE, &oldval) == 0) {
        if (oldval == NULL)
	    sdb_get(options, opt, SDB_ICASE, &oldval);


	if ((admin == 0) && (oldval != NULL) && (*oldval != 'W')) {
	    sdb_unlock(dbname, opt, SDB_ICASE);
	    return (-1);
	}
    }


    newval = malloc(strlen(value) + 3);
    if (newval == NULL) {
	sdb_unlock(dbname, opt, SDB_ICASE);
	return (-1);
    }


    if (!globflag) {
	delta = 0;
	if (oldval && *oldval == 'W') delta = 2 - strlen(oldval) - strlen(opt);
	if (!type) delta += strlen(opt) + strlen(value);
	if ((result = option_doquota(user, delta)) < 0) {
	    free(newval);
	    sdb_unlock(dbname, opt, SDB_ICASE);
	    return (result);
	}
    }


    *newval = "WRN"[type];
    newval[1] = ' ';
    strcpy(newval + 2, value);


    result = sdb_set(dbname, opt, SDB_ICASE, newval);
    if (sdb_unlock(dbname, opt, SDB_ICASE) < 0) result = -1;
    free(newval);


    if (result < 0) option_doquota(user, -delta);

    return (result);
}
