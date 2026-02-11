mouse_click_callback(GtkWidget *text_view,
	GdkEventButton *event)
{
	gint x, y;
	gchar *url = NULL;

	if (event->type != GDK_2BUTTON_PRESS)
		return FALSE;

	gtk_text_view_window_to_buffer_coords(GTK_TEXT_VIEW(text_view),
		GTK_TEXT_WINDOW_WIDGET, event->x, event->y, &x, &y);

	get_url_at_location(&url, GTK_TEXT_VIEW(text_view), x, y);

	if (url != NULL) {
		open_url(text_view, url);
	}

	return TRUE;
}
