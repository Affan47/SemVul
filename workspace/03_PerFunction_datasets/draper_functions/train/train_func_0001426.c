get_cairo_surface()
{
	if (!gtk_widget_get_realized(drawingArea)) {
		return 0;
	}

	return gdk_cairo_create(GDK_DRAWABLE(gtk_widget_get_window(drawingArea)));
}
