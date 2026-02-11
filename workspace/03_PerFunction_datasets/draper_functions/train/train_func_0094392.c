pgd_layers_viewer_drawing_area_expose (GtkWidget      *area,
				       GdkEventExpose *event,
				       PgdLayersDemo  *demo)
{
	cairo_t *cr;

	if (!demo->surface) {
		demo->surface = pgd_layers_render_page (demo);
		if (!demo->surface)
			return FALSE;
	}

	gdk_window_clear (gtk_widget_get_window (area));

	cr = gdk_cairo_create (gtk_widget_get_window (area));
	cairo_set_source_surface (cr, demo->surface, 0, 0);
	cairo_paint (cr);
	cairo_destroy (cr);

	return TRUE;
}
