chat_history_down(chat_window *cw)
{
	GtkTextBuffer *buffer =
		gtk_text_view_get_buffer(GTK_TEXT_VIEW(cw->entry));
	GtkTextIter start, end;
	int p = 0;

	gtk_text_buffer_get_bounds(buffer, &start, &end);

	if (!cw->conv->history || !cw->conv->hist_pos)
		return;

	cw->conv->hist_pos = cw->conv->hist_pos->next;

	gtk_text_buffer_delete(buffer, &start, &end);

	if (cw->conv->hist_pos)
		p = cw_set_message(cw, cw->conv->hist_pos->data);
}
