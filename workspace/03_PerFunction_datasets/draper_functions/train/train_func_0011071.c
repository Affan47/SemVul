ens_util_populate_user_query_fields (GSList *user_query_fields,
                                     const gchar *cue_str,
                                     const gchar *encoded_cue_str)
{
	GString *user_fields;
	GSList *s;

	g_return_val_if_fail (cue_str != NULL, NULL);
	g_return_val_if_fail (encoded_cue_str != NULL, NULL);

	user_fields = g_string_new ("");

	for (s = user_query_fields; s; s = s->next) {
		const gchar *field = s->data;

		if (!field || !*field)
			continue;

		if (*field == '$') {
			g_string_append_printf (user_fields, " (beginswith \"%s\" %s) ", field + 1, encoded_cue_str);
		} else if (*field == '@') {
			g_string_append_printf (user_fields, " (is \"%s\" %s) ", field + 1, encoded_cue_str);
		} else {
			gchar *tmp = name_style_query (field, cue_str);

			g_string_append (user_fields, " ");
			g_string_append (user_fields, tmp);
			g_string_append (user_fields, " ");
			g_free (tmp);
		}
	}

	return g_string_free (user_fields, !user_fields->str || !*user_fields->str);
}
