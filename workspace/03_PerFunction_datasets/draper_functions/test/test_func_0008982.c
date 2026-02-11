loadHistory() {
	GList *tmp;
	char *line, *home_env, *fname;
	FILE *fHnd;

	home_env = getenv("HOME");
	fname = g_strconcat(home_env, DIR_CHAR, DOT_CHAR, "grun_history", NULL);

	fHnd = fopen(fname, "rb");
	g_free(fname);

	if (!fHnd) {
		return NULL;
	}
	tmp = g_list_alloc();
	line = getLine(fHnd);
	if (!line) {
		fclose(fHnd);
		g_list_free(tmp);
		return NULL;
	}
	tmp->data = (gpointer) line;
	while (line) {
		line = getLine(fHnd);
		if (line) {
			tmp = g_list_prepend(tmp, (gpointer) line);
		}
	}
	fclose(fHnd);
	return tmp;
}
