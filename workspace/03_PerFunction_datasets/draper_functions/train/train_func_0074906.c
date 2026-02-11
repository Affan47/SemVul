gpk_log_get_type_line (gchar **array, PkInfoEnum info)
{
	guint i;
	guint size;
	PkInfoEnum info_local;
	const gchar *info_text;
	GString *string;
	gchar *text;
	gchar *whole;
	gchar **sections;

	string = g_string_new ("");
	size = g_strv_length (array);
	info_text = gpk_info_enum_to_localised_past (info);


	for (i=0; i<size; i++) {
		sections = g_strsplit (array[i], "\t", 0);
		info_local = pk_info_enum_from_string (sections[0]);
		if (info_local == info) {
			text = gpk_package_id_format_oneline (sections[1], NULL);
			g_string_append_printf (string, "%s, ", text);
			g_free (text);
		}
		g_strfreev (sections);
	}


	if (string->len == 0) {
		g_string_free (string, TRUE);
		return NULL;
	}


	g_string_set_size (string, string->len - 2);


	text = g_string_free (string, FALSE);
	whole = g_strdup_printf ("<b>%s</b>: %s\n", info_text, text);
	g_free (text);
	return whole;
}
