get_ul(char *u, unsigned long *up, unsigned long def, int base) {
    char *nu;
    int sign = 0;
    unsigned long val;

    if (*u == '+') {
	sign = 1;
	u++;
    } else if (*u == '-') {
	sign = -1;
	u++;
    }
    if (*u) {
	errno = 0;
	val = strtoul(u, &nu, base);
	if (errno == ERANGE) {
	    do_warn(_("number too big\n"));
	    return -1;
	}
	if (*nu) {
	    do_warn(_("trailing junk after number\n"));
	    return -1;
	}
	if (sign == 1)
	    val = def + val;
	else if (sign == -1)
	    val = def - val;
	*up = val;
    } else
	*up = def;
    return 0;
}
