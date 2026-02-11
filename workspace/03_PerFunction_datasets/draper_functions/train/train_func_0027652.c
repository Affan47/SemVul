maildir_dir_name_to_fullname (const gchar *dir_name)
{
	gchar *full_name;

	if (!g_ascii_strncasecmp (dir_name, "..", 2))
		full_name = g_strconcat ("Inbox/", dir_name + 2, NULL);
	else
		full_name = g_strdup (dir_name + 1);

	g_strdelimit (full_name, HIER_SEP, '/');

	if (strchr (full_name, '_')) {
		gint ii, jj;

		for (ii = 0, jj = 0; full_name[ii]; ii++, jj++) {
			if (full_name[ii] == '_' && g_ascii_isxdigit (full_name[ii + 1]) && g_ascii_isxdigit (full_name[ii + 2])) {
				full_name[jj] = 16 * g_ascii_xdigit_value (full_name[ii + 1]) + g_ascii_xdigit_value (full_name[ii + 2]);
				ii += 2;
			} else if (ii != jj) {
				full_name[jj] = full_name[ii];
			}
		}

		full_name[jj] = '\0';
	}

	return full_name;
}
