gsql_source_editor_marker_set (GtkTextIter *iter, gchar *marker_type)
{
	GSQL_TRACE_FUNC;

	GtkSourceMark *pixmark;
	GtkSourceBuffer *buffer;
	GList *markers = NULL;
	buffer = (GtkSourceBuffer *) gtk_text_iter_get_buffer (iter);

	if (buffer)
	{
		pixmark = gtk_source_mark_new (NULL, marker_type);

		gtk_text_buffer_add_mark (GTK_TEXT_BUFFER (buffer), GTK_TEXT_MARK (pixmark), iter);

		markers = g_object_get_data (G_OBJECT (buffer), "markers");
		markers = g_list_append (markers, pixmark);

		HOOKUP_OBJECT_NO_REF (buffer, markers, "markers");
	}

}
