get_language_for_file (GtkTextBuffer *buffer,
		       const gchar   *filename)
{
	GtkSourceLanguageManager *manager;
	GtkSourceLanguage *language;
	GtkTextIter start;
	GtkTextIter end;
	gchar *text;
	gchar *content_type;
	gboolean result_uncertain;

	gtk_text_buffer_get_start_iter (buffer, &start);
	gtk_text_buffer_get_iter_at_offset (buffer, &end, 1024);
	text = gtk_text_buffer_get_slice (buffer, &start, &end, TRUE);

	content_type = g_content_type_guess (filename,
					     (guchar*) text,
					     strlen (text),
					     &result_uncertain);

	if (result_uncertain)
	{
		g_free (content_type);
		content_type = NULL;
	}

	manager = gtk_source_language_manager_get_default ();
	language = gtk_source_language_manager_guess_language (manager,
							       filename,
							       content_type);

	g_message ("Detected '%s' mime type for file %s, chose language %s",
		   content_type != NULL ? content_type : "(null)",
		   filename,
		   language != NULL ? gtk_source_language_get_id (language) : "(none)");

	g_free (content_type);
	g_free (text);
	return language;
}
