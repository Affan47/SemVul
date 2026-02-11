unrealize (GtkWidget *widget)
{
	NemoDesktopWindow *window;
	NemoDesktopWindowDetails *details;
	GdkWindow *root_window;

	window = NEMO_DESKTOP_WINDOW (widget);
	details = window->details;

	root_window = gdk_screen_get_root_window (
				gtk_window_get_screen (GTK_WINDOW (window)));

	gdk_property_delete (root_window,
			     gdk_atom_intern ("NEMO_DESKTOP_WINDOW_ID", TRUE));

	if (details->size_changed_id != 0) {
		g_signal_handler_disconnect (gtk_window_get_screen (GTK_WINDOW (window)),
					     details->size_changed_id);
		details->size_changed_id = 0;
	}

	GTK_WIDGET_CLASS (nemo_desktop_window_parent_class)->unrealize (widget);
}
