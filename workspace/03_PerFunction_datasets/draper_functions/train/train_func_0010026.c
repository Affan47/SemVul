symbols_open(symbols_t *st, const char *exe, const char *nm)
{
	FILE *f;

	st->stale = FALSE;

	f = fopen(nm, "r");

	if (NULL == f) {
		s_warning("can't open \"%s\": %m", nm);
	} else {
		if (!symbols_header_check(f, exe)) {
			s_warning("file \"%s\" not holding symbols for \"%s\"", nm, exe);
			fclose(f);
			f = NULL;
		}
	}


	return f;
}
