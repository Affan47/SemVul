xstuff_zoom_animate (GtkWidget *widget, GdkRectangle *opt_rect)
{
	GdkScreen *gscreen;
	GdkRectangle rect, dest;
	GtkAllocation allocation;
	int monitor;

	if (opt_rect)
		rect = *opt_rect;
	else {
		gdk_window_get_origin (gtk_widget_get_window (widget), &rect.x, &rect.y);
		gtk_widget_get_allocation (widget, &allocation);
		if (!gtk_widget_get_has_window (widget)) {
			rect.x += allocation.x;
			rect.y += allocation.y;
		}
		rect.height = allocation.height;
		rect.width = allocation.width;
	}

	gscreen = gtk_widget_get_screen (widget);
	monitor = gdk_screen_get_monitor_at_window (gscreen, gtk_widget_get_window (widget));
	gdk_screen_get_monitor_geometry (gscreen, monitor, &dest);

	draw_zoom_animation (gscreen,
			     rect.x, rect.y, rect.width, rect.height,
			     dest.x, dest.y, dest.width, dest.height,
			     MINIATURIZE_ANIMATION_STEPS_Z);
}
