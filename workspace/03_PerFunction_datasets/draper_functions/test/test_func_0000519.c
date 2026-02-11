make_components(const char *s, int lineno, int *verbosity)
{
	char *w;
	unsigned int res = 0;
	char *stringp = ast_strdupa(s);
	unsigned int x;

	*verbosity = 3;

	while ((w = strsep(&stringp, ","))) {
		w = ast_skip_blanks(w);

		if (!strcmp(w, "*")) {
			res = 0xFFFFFFFF;
			break;
		} else if (!strncasecmp(w, "verbose(", 8) && sscanf(w + 8, "%d)", verbosity) == 1) {
			res |= (1 << __LOG_VERBOSE);
		} else for (x = 0; x < ARRAY_LEN(levels); x++) {
			if (levels[x] && !strcasecmp(w, levels[x])) {
				res |= (1 << x);
				break;
			}
		}
	}

	return res;
}
