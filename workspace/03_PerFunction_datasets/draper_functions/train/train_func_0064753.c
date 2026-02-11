search_str_in_text (const gchar* search_entry, const gchar* editor_text, gboolean case_sensitive, gint * start_pos, gint * end_pos)
{
	gboolean found;

	if (strlen (editor_text) >= strlen (search_entry))
	{
		gchar* selected_text_case;
		gchar* search_text_case;

		if (case_sensitive)
		{
			selected_text_case = g_strdup (editor_text);
			search_text_case = g_strdup (search_entry);
		}
		else
		{
			selected_text_case = g_utf8_casefold (editor_text, strlen (editor_text));
			search_text_case = g_utf8_casefold (search_entry, strlen (search_entry));
		}

		gchar* strstr = g_strstr_len (selected_text_case, -1, search_text_case);

		if (strstr)
		{
			*start_pos = g_utf8_pointer_to_offset(selected_text_case, strstr);
			*end_pos = g_utf8_pointer_to_offset(selected_text_case, strstr + strlen (search_entry));
			found = TRUE;
		}

		g_free (selected_text_case);
		g_free (search_text_case);
	}

	return found;
}
