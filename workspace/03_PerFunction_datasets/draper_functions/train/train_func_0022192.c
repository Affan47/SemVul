gm_scroll_end(GtkTextView *view, gboolean needs) {
	GtkTextBuffer *buf;
	GtkTextMark *mark;
	GtkTextIter iter;

	if (!needs) {
		return;
	}

	buf = gtk_text_view_get_buffer(view);
	mark = gtk_text_buffer_get_mark(buf, "end-of-buffer");

	if (mark == NULL) {
		gtk_text_buffer_get_end_iter(buf, &iter);
		mark = gtk_text_buffer_create_mark(buf, "end-of-buffer", &iter, FALSE);
	}

	gtk_text_view_scroll_to_mark(view, mark, 0.0, TRUE, 1.0, 1.0);
}
