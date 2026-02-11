get_chars (GtkTextBuffer *buffer,
           gint           start,
           gint           end)
{
	GtkTextIter start_iter;
	GtkTextIter end_iter;

	gtk_text_buffer_get_iter_at_offset (buffer, &start_iter, start);

	if (end < 0)
		gtk_text_buffer_get_end_iter (buffer, &end_iter);
	else
		gtk_text_buffer_get_iter_at_offset (buffer, &end_iter, end);

	return gtk_text_buffer_get_slice (buffer, &start_iter, &end_iter, TRUE);
}
