gpk_update_viewer_textview_visibility_notify_event (GtkWidget *text_view, GdkEventVisibility *event)
{
	gint wx, wy, bx, by;
	GdkWindow *window;
	GdkDevice *device;

	window = gtk_widget_get_window (text_view);
	device = gdk_event_get_device ((const GdkEvent *) event);
	if (device == NULL)
		goto out;
	gdk_window_get_device_position (window,
					device,
					&wx, &wy,
					NULL);

	gtk_text_view_window_to_buffer_coords (GTK_TEXT_VIEW (text_view), GTK_TEXT_WINDOW_WIDGET, wx, wy, &bx, &by);
	gpk_update_viewer_textview_set_cursor (GTK_TEXT_VIEW (text_view), bx, by);
out:
	return FALSE;
}
