append_all_converted (GString        *str,
		      ConversionType  conversion,
		      GSList         *args,
		      gboolean        in_single_quotes,
		      gboolean        in_double_quotes,
		      AddedStatus     added_status)
{
	GSList *l;

	for (l = args; l; l = l->next) {
		char *converted;
		char *escaped;

		if (!(converted = convert_uri (l->data, conversion)))
			continue;

		g_string_append (str, " ");

		escaped = escape_single_quotes (converted,
						in_single_quotes,
						in_double_quotes);
		g_string_append (str, escaped);

		g_free (escaped);
		g_free (converted);
	}

	return ADDED_ALL;
}
