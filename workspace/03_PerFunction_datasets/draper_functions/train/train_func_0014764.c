pk_main_draw_window (PkPlugin *plugin)
{
	cairo_t *cr;
	GdkWindow *gdk_window;


	g_object_get (plugin, "gdk-window", &gdk_window, NULL);

	if (gdk_window == NULL) {
		g_debug ("gdk_window is NULL!");
		return;
	}

	cr = gdk_cairo_create (gdk_window);
	pk_plugin_draw (plugin, cr);
	cairo_destroy (cr);
}
