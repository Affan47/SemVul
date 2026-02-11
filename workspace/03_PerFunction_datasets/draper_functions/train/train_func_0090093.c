panel_background_get_pattern_for_widget (PanelBackground *background,
                                         GtkWidget       *widget)
{
	GtkAllocation    allocation;
	cairo_t         *cr;
        cairo_surface_t *surface;
        cairo_surface_t *bg_surface;
	cairo_pattern_t *pattern;
        cairo_matrix_t   matrix;

        if (!background->composited_pattern)
                return NULL;

        if (cairo_pattern_get_surface (background->composited_pattern, &bg_surface) != CAIRO_STATUS_SUCCESS)
                return NULL;

	gtk_widget_get_allocation (widget, &allocation);
        surface = cairo_image_surface_create (CAIRO_FORMAT_RGB24,
                                              allocation.width, allocation.height);

	cr = cairo_create (surface);
        cairo_set_source_surface (cr, bg_surface, -allocation.x, -allocation.y);
        cairo_rectangle (cr, 0, 0, allocation.width, allocation.height);
        cairo_fill (cr);
        cairo_destroy (cr);

        pattern = cairo_pattern_create_for_surface (surface);
        cairo_matrix_init_translate (&matrix, 0, 0);
        cairo_matrix_scale (&matrix, allocation.width, allocation.height);
        cairo_pattern_set_matrix (pattern, &matrix);
        cairo_pattern_set_extend (pattern, CAIRO_EXTEND_PAD);

        cairo_surface_destroy (surface);

        return pattern;
}
