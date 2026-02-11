gnome_canvas_request_redraw (GnomeCanvas *canvas,
                             gint x1,
                             gint y1,
                             gint x2,
                             gint y2)
{
	GdkRectangle area, clip;

	g_return_if_fail (GNOME_IS_CANVAS (canvas));

	if (!gtk_widget_is_drawable (GTK_WIDGET (canvas)) || (x1 >= x2) || (y1 >= y2))
		return;

	area.x = x1;
	area.y = y1;
	area.width = x2 - x1 + 1;
	area.height = y2 - y1 + 1;

	get_visible_rect (canvas, &clip);
	if (!gdk_rectangle_intersect (&area, &clip, &area))
		return;

	gdk_window_invalidate_rect (
		gtk_layout_get_bin_window (GTK_LAYOUT (canvas)),
		&area, FALSE);
}
