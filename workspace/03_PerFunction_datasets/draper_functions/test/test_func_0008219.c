log_window_jump_to_error(LogWindow *logwin)
{
	GtkTextIter iter;
	gtk_text_buffer_get_end_iter(logwin->buffer, &iter);
	if (!gtk_text_iter_backward_to_tag_toggle(&iter, logwin->error_tag))
		return;

	gtk_text_iter_backward_line(&iter);
	gtk_text_view_scroll_to_iter(GTK_TEXT_VIEW(logwin->text), &iter, 0, TRUE, 0, 0);
}
