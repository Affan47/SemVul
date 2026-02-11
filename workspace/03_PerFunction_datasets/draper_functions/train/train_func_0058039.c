split_cfg_path(const char *path, int *pargc, char ***pargv,
	       grecs_value_t ***pvalv)
{
	int argc;
	char **argv;
	char *delim = ".";
	char static_delim[2] = { 0, 0 };

	if (path[0] == '\\') {
		argv = calloc(2, sizeof (*argv));
		if (!argv)
			return WRDSE_NOSPACE;
		argv[0] = strdup(path + 1);
		if (!argv[0]) {
			free(argv);
			return WRDSE_NOSPACE;
		}
		argv[1] = NULL;
		argc = 1;
	} else {
		int rc;
		struct wordsplit ws;

		if (strchr("./:;,^~", path[0])) {
			delim = static_delim;
			delim[0] = path[0];
			path++;
		}
		ws.ws_delim = delim;

		rc = wordsplit(path, &ws,
			       WRDSF_DELIM | WRDSF_DEFFLAGS);
		if (rc)
			return rc;
		argc = ws.ws_wordc;
		argv = ws.ws_wordv;
		ws.ws_wordc = 0;
		ws.ws_wordv = NULL;
		wordsplit_free(&ws);
	}

	*pargv = argv;
	*pargc = argc;
	if (pvalv) {
		int i;
		grecs_value_t **valv;

		valv = grecs_calloc(argc, sizeof(valv[0]));
		for (i = 0; i < argc; i++) {
			char *p = strchr(argv[i], '=');
			if (p) {
				*p++ = 0;
				valv[i] = parse_label(p);
			}
		}
		*pvalv = valv;
	}
	return 0;
}
