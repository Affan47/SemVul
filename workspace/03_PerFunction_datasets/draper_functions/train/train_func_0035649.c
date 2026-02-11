invalidate_drawing_area(GtkWidget *widget, cairo_rectangle_t r)
{
	GdkRectangle s;

	s = cairo_rect_to_gdk(&r);
	if (widget->window != NULL)
	{
		gdk_window_invalidate_rect(widget->window, &s, TRUE);
	}
}
