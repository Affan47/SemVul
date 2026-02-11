__db_getlong(dbenv, progname, p, min, max, storep)
	DB_ENV *dbenv;
	const char *progname;
	char *p;
	long min, max, *storep;
{
	long val;
	char *end;

	__os_set_errno(0);
	val = strtol(p, &end, 10);
	if ((val == LONG_MIN || val == LONG_MAX) &&
	    __os_get_errno() == ERANGE) {
		if (dbenv == NULL)
			fprintf(stderr, "%s: %s: %s\n",
			    progname, p, strerror(ERANGE));
		else
			dbenv->err(dbenv, ERANGE, "%s", p);
		return (ERANGE);
	}
	if (p[0] == '\0' || (end[0] != '\0' && end[0] != '\n')) {
		if (dbenv == NULL)
			fprintf(stderr, DB_STR_A("0042",
			    "%s: %s: Invalid numeric argument\n",
			    "%s %s\n"), progname, p);
		else
			dbenv->errx(dbenv, DB_STR_A("0043",
			    "%s: Invalid numeric argument", "%s"), p);
		return (EINVAL);
	}
	if (val < min) {
		if (dbenv == NULL)
			fprintf(stderr, DB_STR_A("0044",
			    "%s: %s: Less than minimum value (%ld)\n",
			    "%s %s %ld\n"), progname, p, min);
		else
			dbenv->errx(dbenv, DB_STR_A("0045",
			    "%s: Less than minimum value (%ld)",
			    "%s %ld"), p, min);
		return (ERANGE);
	}
	if (val > max) {
		if (dbenv == NULL)
			fprintf(stderr, DB_STR_A("0046",
			    "%s: %s: Greater than maximum value (%ld)\n",
			    "%s %s %ld\n"), progname, p, max);
		else
			dbenv->errx(dbenv, DB_STR_A("0047",
			    "%s: Greater than maximum value (%ld)",
			    "%s %ld"), p, max);
		return (ERANGE);
	}
	*storep = val;
	return (0);
}
