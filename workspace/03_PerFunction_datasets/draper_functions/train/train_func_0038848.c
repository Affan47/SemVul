magicopt(name, val, user)
    char *name, *val, *user;
{
    char *tmp;
    static char magicbuf[256];

    if (*val == '\0') {
	if (!strcasecmp(name, opt_date)) {
	    return (n_arpadate());
	}
	if (!strcasecmp(name, opt_from) && *user) {
	    tmp = option_get("", opt_domain, 1, NULL);
	    *magicbuf = '\0';
	    if (tmp != NULL) {
		snprintf(magicbuf, sizeof(magicbuf), "%s@%s", user, tmp);
		free(tmp);
	    }
	    return (magicbuf);
	}
    } else if (!strcasecmp(name, opt_usage)) {
	snprintf(magicbuf, sizeof(magicbuf), "%ld", (long) ((atol(val) + 1023) / 1024));

	return (magicbuf);
    }

    return (val);
}
