compute_indentation(GtkTextBuffer *buffer, GtkTextIter *iter, gint line)
{
	GtkTextIter start_iter, end_iter;
	gunichar ch;

	gtk_text_buffer_get_iter_at_line(buffer, &start_iter, line);
	end_iter = start_iter;
	ch = gtk_text_iter_get_char(&end_iter);
	while (g_unichar_isspace(ch) && ch != '\n') {
		if (!gtk_text_iter_forward_char(&end_iter))
			break;
		ch = gtk_text_iter_get_char(&end_iter);
	}
	if (gtk_text_iter_equal(&start_iter, &end_iter))
		return NULL;

	if (iter && gtk_text_iter_compare(iter, &end_iter) < 0)
		return gtk_text_iter_get_text(&start_iter, iter);
	return gtk_text_iter_get_text(&start_iter, &end_iter);
}
