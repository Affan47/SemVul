repeat (ccss_cairo_image_t const	*image,
	cairo_t				*cr,
	int32_t				 width,
	int32_t				 height,
	double				 tile_width,
	double				 tile_height)
{
	cairo_pattern_t	*pattern;


	pattern = create_pattern (image,
				  width + tile_width,
				  height + tile_height);
	g_return_if_fail (pattern);

	cairo_pattern_set_extend (pattern, CAIRO_EXTEND_NONE);
	cairo_set_source (cr, pattern);
	cairo_pattern_destroy (pattern), pattern = NULL;
	cairo_fill_preserve (cr);
}
