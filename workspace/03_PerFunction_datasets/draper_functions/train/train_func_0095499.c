ch_ccmx_gen_window_move (ChCcmxPrivate *priv)
{
	const gchar *xrandr_name;
	gchar *plug_name;
	GdkRectangle rect;
	GdkScreen *screen;
	gint i;
	gint monitor_num = -1;
	gint num_monitors;
	gint win_height;
	gint win_width;
	GtkWindow *window;


	screen = gdk_screen_get_default ();
	num_monitors = gdk_screen_get_n_monitors (screen);
	xrandr_name = cd_device_get_metadata_item (priv->gen_device,
						   CD_DEVICE_METADATA_XRANDR_NAME);
	for (i = 0; i < num_monitors; i++) {
		plug_name = gdk_screen_get_monitor_plug_name (screen, i);
		if (g_strcmp0 (plug_name, xrandr_name) == 0)
			monitor_num = i;
		g_free (plug_name);
	}
	if (monitor_num == -1) {
		g_warning ("failed to find output %s", xrandr_name);
		goto out;
	}


	gdk_screen_get_monitor_geometry (screen, monitor_num, &rect);
	window = GTK_WINDOW (gtk_builder_get_object (priv->builder, "dialog_ccmx"));
	gtk_window_get_size (window, &win_width, &win_height);
	gtk_window_move (window,
			 rect.x + ((rect.width - win_width) / 2),
			 rect.y + ((rect.height - win_height) / 2));
out:
	return;
}
