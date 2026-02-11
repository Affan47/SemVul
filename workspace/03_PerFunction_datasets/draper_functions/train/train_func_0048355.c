cairo_font_scaling(cairo_surface_t *surface, double tile_w, double tile_h, double font_w, double font_h)
{
	cairo_t *cr;
	cairo_matrix_t m;
	double sx, sy;

	if (surface != NULL)
	{
	cr = cairo_create(surface);
	if (cr !=NULL)
	{

		cairo_get_matrix(cr, &m);
		sx = (tile_w)/(font_w);
		sy = (tile_h)/(font_h);
		cairo_matrix_scale(&m, sx, sy);
	}

	cairo_destroy(cr);
	}
	return(m);
}
