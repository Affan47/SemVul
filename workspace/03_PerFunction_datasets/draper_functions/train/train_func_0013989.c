open_file (TestSearch  *search,
	   const gchar *filename)
{
	gchar *contents;
	GError *error = NULL;
	GtkSourceLanguageManager *language_manager;
	GtkSourceLanguage *language;
	GtkTextIter iter;

	if (!g_file_get_contents (filename, &contents, NULL, &error))
	{
		g_error ("Impossible to load file: %s", error->message);
	}

	gtk_text_buffer_set_text (GTK_TEXT_BUFFER (search->priv->source_buffer),
				  contents,
				  -1);

	language_manager = gtk_source_language_manager_get_default ();
	language = gtk_source_language_manager_get_language (language_manager, "c");
	gtk_source_buffer_set_language (search->priv->source_buffer, language);

	gtk_text_buffer_get_start_iter (GTK_TEXT_BUFFER (search->priv->source_buffer),
					&iter);

	gtk_text_buffer_select_range (GTK_TEXT_BUFFER (search->priv->source_buffer),
				      &iter,
				      &iter);

	g_free (contents);
}
