set_mouse_cursor(GtkTextView *text_view, gint x, gint y)
{
	gchar *url = NULL;
	gboolean hovering = FALSE;

	get_url_at_location(&url, GTK_TEXT_VIEW(text_view), x, y);

	if (url)
		hovering = TRUE;

	if (hovering != HOVERING_OVER_LINK) {
		HOVERING_OVER_LINK = hovering;

		if (HOVERING_OVER_LINK)
			gdk_window_set_cursor(gtk_text_view_get_window
				(text_view, GTK_TEXT_WINDOW_TEXT), hand_cursor);
		else
			gdk_window_set_cursor(gtk_text_view_get_window
				(text_view, GTK_TEXT_WINDOW_TEXT),
				regular_cursor);

	}
}
