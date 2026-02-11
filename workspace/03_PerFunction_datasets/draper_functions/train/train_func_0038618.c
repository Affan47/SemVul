list_add_file(GList *list, const char *name, const char *default_path)
{
	struct stat statbuf;
	char *fname;

	g_return_val_if_fail(name != NULL, NULL);

	fname = convert_home(name);
	if (USE_DEFAULT_PATH(fname, default_path)) {
                g_free(fname);
		fname = g_strconcat(default_path, G_DIR_SEPARATOR_S,
				    name, NULL);
	}
	if (stat(fname, &statbuf) == 0) {
		list = g_list_append(list, !S_ISDIR(statbuf.st_mode) ? g_strdup(name) :
				     g_strconcat(name, G_DIR_SEPARATOR_S, NULL));
	}

        g_free(fname);
	return list;
}
