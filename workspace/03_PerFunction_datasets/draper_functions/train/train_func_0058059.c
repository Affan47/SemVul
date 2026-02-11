pick_lang_for_mime_type_pass (GtkSourceLanguageManager *lm,
			      const char               *mime_type,
			      gboolean                  exact_match)
{
	const gchar* const * id_ptr;

	for (id_ptr = gtk_source_language_manager_get_language_ids (lm);
	     id_ptr != NULL && *id_ptr != NULL;
	     id_ptr++)
	{
		GtkSourceLanguage *lang;
		gchar **mime_types, **mptr;

		lang = gtk_source_language_manager_get_language (lm, *id_ptr);
		mime_types = gtk_source_language_get_mime_types (lang);

		for (mptr = mime_types; mptr != NULL && *mptr != NULL; mptr++)
		{
			gboolean matches;

			if (exact_match)
				matches = strcmp (mime_type, *mptr) == 0;
			else
				matches = g_content_type_is_a (mime_type, *mptr);

			if (matches)
			{
				g_strfreev (mime_types);
				return lang;
			}
		}

		g_strfreev (mime_types);
	}

	return NULL;
}
