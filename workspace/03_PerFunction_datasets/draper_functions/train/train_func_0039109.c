totem_interface_set_transient_for (GtkWindow *window, GtkWindow *parent)
{
#ifdef GDK_WINDOWING_X11
	GdkDisplay *display;

	display = gdk_display_get_default ();

	if (GDK_IS_X11_DISPLAY (display) &&
	    GTK_IS_PLUG (parent)) {
		GdkWindow *toplevel;

		gtk_widget_realize (GTK_WIDGET (window));
		toplevel = totem_gtk_plug_get_toplevel (GTK_PLUG (parent));
		if (toplevel != NULL) {
			gdk_window_set_transient_for
				(gtk_widget_get_window (GTK_WIDGET (window)), toplevel);
			g_object_unref (toplevel);
		}
		return;
	}
#endif

	gtk_window_set_transient_for (GTK_WINDOW (window),
				      GTK_WINDOW (parent));
}
