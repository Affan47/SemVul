regexp_init(const char *regexp)
{
    int rc;

    assert(!regexp_compiled);

    rc = regcomp(&search_regexp, regexp, REG_EXTENDED
#ifndef NANO_TINY
	| (ISSET(CASE_SENSITIVE) ? 0 : REG_ICASE)
#endif
	);

    if (rc != 0) {
	size_t len = regerror(rc, &search_regexp, NULL, 0);
	char *str = charalloc(len);

	regerror(rc, &search_regexp, str, len);
	statusbar(_("Bad regex \"%s\": %s"), regexp, str);
	free(str);

	return FALSE;
    }

    regexp_compiled = TRUE;

    return TRUE;
}
