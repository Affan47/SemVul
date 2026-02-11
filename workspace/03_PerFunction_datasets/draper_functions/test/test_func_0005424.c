gedit_document_set_search_text (GeditDocument *doc,
				const gchar   *text,
				guint          flags)
{
	gchar *converted_text;
	gboolean notify = FALSE;
	GtkSourceSearchContext *search_context;

	g_return_if_fail (GEDIT_IS_DOCUMENT (doc));
	g_return_if_fail ((text == NULL) || g_utf8_validate (text, -1, NULL));

	gedit_debug_message (DEBUG_DOCUMENT, "text = %s", text);

	if (text != NULL)
	{
		if (*text != '\0')
		{
			converted_text = gtk_source_utils_unescape_search_text (text);
			notify = !gedit_document_get_can_search_again (doc);
		}
		else
		{
			converted_text = g_strdup ("");
			notify = gedit_document_get_can_search_again (doc);
		}

		gtk_source_search_settings_set_search_text (doc->priv->deprecated_search_settings,
							    converted_text);

		g_free (converted_text);
	}

	if (!GEDIT_SEARCH_IS_DONT_SET_FLAGS (flags))
	{
		gtk_source_search_settings_set_case_sensitive (doc->priv->deprecated_search_settings,
							       GEDIT_SEARCH_IS_CASE_SENSITIVE (flags));

		gtk_source_search_settings_set_at_word_boundaries (doc->priv->deprecated_search_settings,
								   GEDIT_SEARCH_IS_ENTIRE_WORD (flags));
	}

	search_context = get_deprecated_search_context (doc);

	if (search_context == NULL)
	{
		search_context = gtk_source_search_context_new (GTK_SOURCE_BUFFER (doc),
								doc->priv->deprecated_search_settings);

		_gedit_document_set_search_context (doc, search_context);

		g_object_unref (search_context);
	}

	if (notify)
	{
		g_object_notify (G_OBJECT (doc), "can-search-again");
	}
}
