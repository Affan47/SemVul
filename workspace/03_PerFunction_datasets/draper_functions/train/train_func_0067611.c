results_on_text_view_motion(GtkWidget * widget, GdkEventMotion * event, gpointer user_data __attribute__ ((unused)))
{
	GtkTextBuffer *buffer;
	GtkTextView *textview;
	GdkCursor *cursor;
	GtkTextIter iter;
	GSList *tags, *tagp;
	gint x, ex, ey, y;
	int hovering = 0;

	textview = GTK_TEXT_VIEW(widget);

	if (event->is_hint) {
		gdk_window_get_pointer(event->window, &ex, &ey, NULL);
	} else {
		ex = event->x;
		ey = event->y;
	}

	gtk_text_view_window_to_buffer_coords(textview, GTK_TEXT_WINDOW_WIDGET, ex, ey, &x, &y);
	buffer = gtk_text_view_get_buffer(textview);
	gtk_text_view_get_iter_at_location(textview, &iter, x, y);
	tags = gtk_text_iter_get_tags(&iter);
	for (tagp = tags; tagp != NULL; tagp = tagp->next) {
		if (strncmp(GTK_TEXT_TAG(tagp->data)->name, "line", 4) == 0 ||
		    strcmp(GTK_TEXT_TAG(tagp->data)->name, "inline-link") == 0) {
			hovering = TRUE;
			break;
		}
	}
	if (hovering) {
		cursor = gdk_cursor_new(GDK_HAND2);
		gdk_window_set_cursor(event->window, cursor);
		gdk_cursor_unref(cursor);
		gdk_flush();
	} else {
		gdk_window_set_cursor(event->window, NULL);
	}
	g_slist_free(tags);
	return FALSE;
}
