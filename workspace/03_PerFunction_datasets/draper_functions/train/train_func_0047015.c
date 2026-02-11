on_insert_text (GtkTextBuffer *buffer,
                GtkTextIter   *location,
                gchar         *text,
                gint           len,
                Sourceview    *sv)
{
	int i = 0, lines = 0;
	gchar* signal_text;
	SourceviewCell *cell = sourceview_cell_new (location, GTK_TEXT_VIEW (sv->priv->view));
	IAnjutaIterable *iter = ianjuta_iterable_clone (IANJUTA_ITERABLE (cell), NULL);
	GtkTextMark *mark = gtk_text_buffer_create_mark (buffer, NULL, location, TRUE);
	g_object_unref (cell);

	ianjuta_iterable_set_position (iter,
	                               ianjuta_iterable_get_position (iter, NULL) - len,
	                               NULL);


	g_signal_emit_by_name (G_OBJECT (sv), "update-ui");

	if (len <= 1 && strlen (text) <= 1)
	{

		g_signal_emit_by_name (G_OBJECT (sv), "char-added", iter, text[0]);
		gtk_text_buffer_get_iter_at_mark (buffer, location, mark);
	}

	for (i = 0; i < len; i ++)
		if (text[i] == '\n')
			lines ++;


	signal_text = g_strndup (text, len);

	g_signal_emit_by_name (G_OBJECT (sv), "changed", iter, TRUE, len, lines, signal_text);
	g_free (signal_text);

	gtk_text_buffer_get_iter_at_mark (buffer, location, mark);
}
