cell_renderer_color_get_size (GtkCellRenderer *cell,
                              GtkWidget *widget,
                              const GdkRectangle *cell_area,
                              gint *x_offset,
                              gint *y_offset,
                              gint *width,
                              gint *height)
{
	gint color_width  = 16;
	gint color_height = 16;
	gint calc_width;
	gint calc_height;
	gfloat xalign;
	gfloat yalign;
	guint xpad;
	guint ypad;

	g_object_get (
		cell, "xalign", &xalign, "yalign", &yalign,
		"xpad", &xpad, "ypad", &ypad, NULL);

	calc_width  = (gint) xpad * 2 + color_width;
	calc_height = (gint) ypad * 2 + color_height;

	if (cell_area && color_width > 0 && color_height > 0) {
		if (x_offset) {
			*x_offset = (((gtk_widget_get_direction (widget) == GTK_TEXT_DIR_RTL) ?
					(1.0 - xalign) : xalign) *
					(cell_area->width - calc_width));
			*x_offset = MAX (*x_offset, 0);
		}

		if (y_offset) {
			*y_offset =(yalign *
				(cell_area->height - calc_height));
			*y_offset = MAX (*y_offset, 0);
		}
	} else {
		if (x_offset) *x_offset = 0;
		if (y_offset) *y_offset = 0;
	}

	if (width)
		*width = calc_width;

	if (height)
		*height = calc_height;
}
