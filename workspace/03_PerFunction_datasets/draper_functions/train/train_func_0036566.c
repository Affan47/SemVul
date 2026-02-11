util_find_program_in_path (const gchar * program, const gchar * path)
{
	const gchar *p;
	gchar *name, *freeme, *user_path = NULL;
	size_t len;
	size_t pathlen;

	g_return_val_if_fail (program != NULL, NULL);


	if (g_path_is_absolute (program)
	    || strchr (program, G_DIR_SEPARATOR) != NULL) {
		if (g_file_test (program, G_FILE_TEST_IS_EXECUTABLE))
			return g_strdup (program);
		else
			return NULL;
	}

	if (path == NULL) {
		path = g_getenv ("PATH");

		if (path == NULL) {
			path = "/bin:/usr/bin:.";
		}


		user_path = g_strconcat (path, ":", EXTRA_PATH, NULL);
		path = user_path;
	}

	len = strlen (program) + 1;
	pathlen = strlen (path);
	freeme = name = g_malloc (pathlen + len + 1);


	memcpy (name + pathlen + 1, program, len);
	name = name + pathlen;

	*name = G_DIR_SEPARATOR;

	p = path;
	do {
		char *startp;

		path = p;
		p = my_strchrnul (path, G_SEARCHPATH_SEPARATOR);

		if (p == path)


			startp = name + 1;
		else
			startp =
			    memcpy (name - (p - path), path, p - path);

		if (g_file_test (startp, G_FILE_TEST_IS_EXECUTABLE)) {
			gchar *ret;
			ret = g_strdup (startp);
			g_free (freeme);
			g_free (user_path);
			return ret;
		}
	}
	while (*p++ != '\0');

	g_free (freeme);
	g_free (user_path);

	return NULL;
}
