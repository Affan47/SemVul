_wapi_dirname (const gchar *filename)
{
	gchar *new_filename = g_strdup (filename), *ret;

	if (IS_PORTABILITY_SET) {
		g_strdelimit (new_filename, "\\", '/');
	}

	if (IS_PORTABILITY_DRIVE &&
	    g_ascii_isalpha (new_filename[0]) &&
	    (new_filename[1] == ':')) {
		int len = strlen (new_filename);

		g_memmove (new_filename, new_filename + 2, len - 2);
		new_filename[len - 2] = '\0';
	}

	ret = g_path_get_dirname (new_filename);
	g_free (new_filename);

	return(ret);
}
