get_first_volume_name (const char           *name,
		       const char           *pattern,
		       FirstVolumeExtension  extension_type)
{
	char   *volume_name = NULL;
	GRegex *re;

	re = g_regex_new (pattern, G_REGEX_CASELESS, 0, NULL);
	if (g_regex_match (re, name, 0, NULL)) {
		char **parts;
		int    l, i;

		parts = g_regex_split (re, name, 0);
		l = strlen (parts[2]);
		switch (extension_type) {
		case FIRST_VOLUME_IS_000:
			for (i = 0; i < l; i++)
				parts[2][i] = '0';
			break;

		case FIRST_VOLUME_IS_001:
			for (i = 0; i < l; i++)
				parts[2][i] = (i < l - 1) ? '0' : '1';
			break;

		case FIRST_VOLUME_IS_RAR:
			if (g_str_has_suffix (parts[1], "r")) {
				parts[2][0] = 'a';
				parts[2][1] = 'r';
			}
			else {
				parts[2][0] = 'A';
				parts[2][1] = 'R';
			}
			break;
		}

		volume_name = g_strjoinv ("", parts);

		g_strfreev (parts);
	}
	g_regex_unref (re);

	if (volume_name != NULL) {
		char *tmp;

		tmp = volume_name;
		volume_name = g_filename_from_utf8 (tmp, -1, NULL, NULL, NULL);
		g_free (tmp);
	}

	return volume_name;
}
