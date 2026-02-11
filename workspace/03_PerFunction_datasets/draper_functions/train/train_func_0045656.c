draw_color_each_monitor (GnomeBG *bg,
			 GdkPixbuf *dest,
			 GdkScreen *screen)
{
	GdkRectangle rect;
	gint num_monitors;
	int monitor;

	num_monitors = gdk_screen_get_n_monitors (screen);
	for (monitor = 0; monitor < num_monitors; monitor++) {
		gdk_screen_get_monitor_geometry (screen, monitor, &rect);
		draw_color_area (bg, dest, &rect);
	}
}
