unescape_html(GtkTextBuffer *buffer, GtkTextMark html_start)
{
	GtkTextIter start, end;
	GtkTextMark *start_mark = NULL, *end_mark = NULL;
	int html_found = 0;

	gtk_text_buffer_get_iter_at_mark(buffer, &start, &html_start);
	gtk_text_buffer_get_iter_at_mark(buffer, &end, &html_start);

	while (search_char(&start, '&') &&
		search_char(&end, ';') &&
		gtk_text_iter_compare(&start, &end) < 0) {
		gchar *code;

		gtk_text_iter_forward_char(&end);

		code = gtk_text_buffer_get_slice(buffer, &start, &end, TRUE);
		start_mark =
			gtk_text_buffer_create_mark(buffer, NULL, &start, TRUE);
		end_mark =
			gtk_text_buffer_create_mark(buffer, NULL, &end, TRUE);

		if (!g_ascii_strncasecmp(code, "&gt;", 4)) {
			gtk_text_buffer_delete(buffer, &start, &end);
			gtk_text_buffer_get_iter_at_mark(buffer, &start,
				start_mark);
			gtk_text_buffer_insert(buffer, &start, ">", -1);
			html_found = 1;
		}
		if (!g_ascii_strncasecmp(code, "&lt;", 4)) {
			gtk_text_buffer_delete(buffer, &start, &end);
			gtk_text_buffer_get_iter_at_mark(buffer, &start,
				start_mark);
			gtk_text_buffer_insert(buffer, &start, "<", -1);
			html_found = 1;
		}
		if (!g_ascii_strncasecmp(code, "&amp;", 5)) {
			gtk_text_buffer_delete(buffer, &start, &end);
			gtk_text_buffer_get_iter_at_mark(buffer, &start,
				start_mark);
			gtk_text_buffer_insert(buffer, &start, "&", -1);
			html_found = 1;
		}
		if (!g_ascii_strncasecmp(code, "&#8212;", 7)) {
			gtk_text_buffer_delete(buffer, &start, &end);
			gtk_text_buffer_get_iter_at_mark(buffer, &start,
				start_mark);
			gtk_text_buffer_insert(buffer, &start, "--", -1);
			html_found = 1;
		}
		if (!g_ascii_strncasecmp(code, "&nbsp;", 6)) {
			gtk_text_buffer_delete(buffer, &start, &end);
			gtk_text_buffer_get_iter_at_mark(buffer, &start,
				start_mark);
			gtk_text_buffer_insert(buffer, &start, " ", -1);
			html_found = 1;
		}
		if (!g_ascii_strncasecmp(code, "&quot;", 6)) {
			gtk_text_buffer_delete(buffer, &start, &end);
			gtk_text_buffer_get_iter_at_mark(buffer, &start,
				start_mark);
			gtk_text_buffer_insert(buffer, &start, "\"", -1);
			html_found = 1;
		}

		if (html_found) {
			gtk_text_buffer_get_iter_at_mark(buffer, &start,
				start_mark);
			gtk_text_buffer_get_iter_at_mark(buffer, &end,
				start_mark);
			gtk_text_iter_forward_char(&end);
		}

		gtk_text_iter_forward_char(&start);
	}
}
