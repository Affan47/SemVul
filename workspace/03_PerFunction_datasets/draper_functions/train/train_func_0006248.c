log_window_insert_text(GtkTextBuffer *buffer, GtkTextIter *iter,
				   const gchar *text, const gchar *tag)
{
	gchar *str_utf8;

	if (!text || !*text) return;

	str_utf8 = utf8_validate_or_convert(text);
	gtk_text_buffer_insert_with_tags_by_name(buffer, iter, str_utf8, -1, tag, NULL);
	g_free(str_utf8);
}
