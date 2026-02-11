brasero_project_name_truncate_label (const gchar *label)
{
	const gchar *delim;
	gchar *next_char;


	delim = label;
	while ((next_char = g_utf8_find_next_char (delim, NULL))) {
		if (next_char - label > 32)
			break;

		delim = next_char;
	}

	return g_strndup (label, delim - label);
}
