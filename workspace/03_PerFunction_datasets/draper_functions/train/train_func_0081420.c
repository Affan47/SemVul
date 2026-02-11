gtk_source_buffer_real_insert_text (GtkTextBuffer *buffer,
				    GtkTextIter   *iter,
				    const gchar   *text,
				    gint           len)
{
	gint start_offset;

	g_return_if_fail (GTK_SOURCE_IS_BUFFER (buffer));
	g_return_if_fail (iter != NULL);
	g_return_if_fail (text != NULL);
	g_return_if_fail (gtk_text_iter_get_buffer (iter) == buffer);

	start_offset = gtk_text_iter_get_offset (iter);


	GTK_TEXT_BUFFER_CLASS (gtk_source_buffer_parent_class)->insert_text (buffer, iter, text, len);

	gtk_source_buffer_content_inserted (buffer,
					    start_offset,
					    gtk_text_iter_get_offset (iter));
}
