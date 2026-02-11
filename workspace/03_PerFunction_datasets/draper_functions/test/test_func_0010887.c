gm_world_text_view_check_buffer_size(GmWorldTextView *view) {
	GtkTextBuffer *buf = GM_WORLD_TEXT_VIEW_BUFFER(view);
	GtkTextIter start, end;

	gint d = gtk_text_buffer_get_line_count(buf) - view->priv->max_lines;

	if (d > 0) {
		gtk_text_buffer_get_iter_at_line(buf, &start, 0);
		gtk_text_buffer_get_iter_at_line(buf, &end, d);


		gm_world_text_view_remove_blinkers(view, &start, &end);

		gtk_text_buffer_delete(buf, &start, &end);
	}
}
