on_delete_range_after (GtkTextBuffer *buffer,
                       GtkTextIter   *start_iter,
                       GtkTextIter   *end_iter,
                       gpointer       user_data)
{
	Sourceview *sv = NULL;
	GtkTextMark *start_mark = NULL, *end_mark = NULL;
	SourceviewCell *cell = NULL;
	IAnjutaIterable *position = NULL;
	gint length = 0, i = 0, lines = 0;


	g_return_if_fail (ANJUTA_IS_SOURCEVIEW (user_data));
	sv = ANJUTA_SOURCEVIEW (user_data);


	cell = sourceview_cell_new (start_iter, GTK_TEXT_VIEW (sv->priv->view));
	position = IANJUTA_ITERABLE (cell);


	length = g_utf8_strlen (sv->priv->deleted_text, -1);
	for (i = 0; i < length; i ++)
		if (sv->priv->deleted_text[i] == '\n')
			lines ++;


	start_mark = gtk_text_buffer_create_mark (buffer, NULL, start_iter, TRUE);
	end_mark   = gtk_text_buffer_create_mark (buffer, NULL, end_iter, TRUE);

	g_signal_emit_by_name (G_OBJECT (sv), "changed",
	                       position, FALSE, length, lines, sv->priv->deleted_text);


	gtk_text_buffer_get_iter_at_mark (buffer, start_iter, start_mark);
	gtk_text_buffer_get_iter_at_mark (buffer, end_iter, end_mark);


	g_free (sv->priv->deleted_text);
	sv->priv->deleted_text = NULL;

}
