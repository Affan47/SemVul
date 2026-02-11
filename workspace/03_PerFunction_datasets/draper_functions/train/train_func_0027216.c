html_text_buffer_append(GtkTextView *text_view, char *txt, int ignore)
{
	gchar *text = convert_to_utf8(txt);
	GtkTextIter iter;
	GtkTextMark *insert_mark;

	GdkRectangle iter_loc;
	GdkRectangle visible_rect;

	GtkTextBuffer *buffer = gtk_text_view_get_buffer(text_view);

	if (strcasestr(text, "<br>")) {
		char *c = text;
		while ((c = strchr(text, '\n')) != 0)
			*c = ' ';
		while ((c = strchr(text, '\r')) != 0)
			*c = ' ';
	} else if (strchr(text, '\r')) {
		char *c = text;
		if (strchr(text, '\n')) {
			while ((c = strchr(c, '\r')) != 0)
				*c = ' ';
		} else {
			while ((c = strchr(c, '\r')) != 0)
				*c = '\n';
		}
	}

	gtk_text_buffer_get_end_iter(buffer, &iter);

	insert_mark = gtk_text_buffer_get_mark(buffer, "real_end_mark");

	if (insert_mark) {
		GtkTextIter del;
		gtk_text_buffer_get_iter_at_mark(buffer, &del, insert_mark);
		gtk_text_buffer_delete(buffer, &del, &iter);
		gtk_text_buffer_get_end_iter(buffer, &iter);
	}
	else
		insert_mark = gtk_text_buffer_create_mark(buffer,
			"real_end_mark", &iter, TRUE);


	gtk_text_view_get_iter_location(text_view, &iter, &iter_loc);
	gtk_text_view_get_visible_rect(text_view, &visible_rect);

	gtk_text_buffer_insert(buffer, &iter, text, -1);
	parse_html(text_view, *insert_mark, ignore);

	if (iter_loc.y <= visible_rect.y + visible_rect.height) {
		GtkTextMark *end_mark;

		gtk_text_buffer_get_end_iter(buffer, &iter);
		end_mark = gtk_text_buffer_create_mark(buffer, NULL, &iter,
			TRUE);

		gtk_text_view_scroll_mark_onscreen(text_view, end_mark);
		gtk_text_buffer_delete_mark(buffer, end_mark);
	}

	if (!(ignore & HTML_IGNORE_END))
		gtk_text_buffer_delete_mark(buffer, insert_mark);

	g_free(text);
}
