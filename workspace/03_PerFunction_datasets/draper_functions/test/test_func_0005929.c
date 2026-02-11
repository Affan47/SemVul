parse_include(const char *text, int once)
{
	struct wordsplit ws;
	char *tmp = NULL;
	char *p = NULL;
	int rc = 1;

	if (wordsplit(text, &ws, WRDSF_DEFFLAGS))
		grecs_error(&LOCUS, 0, _("Cannot parse include line"));
	else if (ws.ws_wordc != 2) {
		wordsplit_free(&ws);
		grecs_error(&LOCUS, 0, _("invalid include statement"));
	} else {
		size_t len;
		int allow_cwd;

		p = ws.ws_wordv[1];
		len = strlen (p);

		if (p[0] == '<' && p[len - 1] == '>') {
			allow_cwd = 0;
			p[len - 1] = 0;
			p++;
		}
		else
			allow_cwd = 1;

		if (p[0] != '/') {
			p = grecs_find_include_file(p, allow_cwd);
			if (!p)
				grecs_error(&LOCUS, 0,
					    _("%s: No such file or directory"),
					    p);
		}
	}

	if (p)
		rc = push_source(p, once);
	grecs_free(tmp);
	wordsplit_free(&ws);
	return rc;
}
