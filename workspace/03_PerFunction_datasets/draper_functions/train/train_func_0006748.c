printing_text_iter_get_offset_bytes(PrintData *print_data, const GtkTextIter *iter)
{
	gint off_bytes;
	gchar *text;
	GtkTextIter start;

	if (print_data->sel_start < 0 || print_data->sel_end <= print_data->sel_start) {
		gtk_text_buffer_get_start_iter(gtk_text_iter_get_buffer(iter), &start);
	} else {
		gtk_text_buffer_get_iter_at_offset(gtk_text_iter_get_buffer(iter), &start, print_data->sel_start);
	}
	text = gtk_text_iter_get_text(&start, iter);
	off_bytes = strlen(text);
	g_free(text);
	return off_bytes;
}
