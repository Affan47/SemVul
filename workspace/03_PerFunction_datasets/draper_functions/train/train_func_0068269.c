maildir_full_name_to_dir_name (const gchar *full_name)
{
	gchar *path;

	if (g_ascii_strcasecmp (full_name, "Inbox") == 0) {
		path = g_strdup (".");
	} else {
		if (g_ascii_strncasecmp (full_name, "Inbox/", 6) == 0)
			path = g_strconcat ("/", full_name + 5, NULL);
		else
			path = g_strconcat ("/", full_name, NULL);

		if (strchr (path, HIER_SEP_CHAR) || strchr (path, '_')) {
			GString *tmp = g_string_new ("");
			const gchar *pp;

			for (pp = path; *pp; pp++) {
				if (*pp == HIER_SEP_CHAR || *pp == '_')
					g_string_append_printf (tmp, "_%02X", *pp);
				else
					g_string_append_c (tmp, *pp);
			}

			g_free (path);
			path = g_string_free (tmp, FALSE);
		}

		g_strdelimit (path, "/", HIER_SEP_CHAR);
	}

	return path;
}
