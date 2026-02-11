find_builtin (const char *fmtstr, int page, gboolean def)
{
	int list_elem = 0;
	char const * const *candidates;

	if (page == GO_FORMAT_UNKNOWN)
		return NULL;

	candidates = _go_format_builtins (page);
	if (!candidates)
		return NULL;

	while (candidates[list_elem]) {
		if (strcmp (candidates[list_elem], fmtstr) == 0)
			break;
		list_elem++;
	}

	if (candidates[list_elem] == NULL &&
	    page == GO_FORMAT_GENERAL &&
	    g_ascii_strcasecmp (candidates[0], fmtstr) == 0)
		list_elem = 0;

	if (candidates[list_elem] == NULL && def)
		list_elem = 0;

	return candidates[list_elem];
}
