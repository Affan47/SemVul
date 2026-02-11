equinox_rectangle_gradient (cairo_t *cr, EquinoxCairoOps ops,
				double x, double y, double w, double h,
				cairo_pattern_t *pattern) {
	cairo_set_source (cr, pattern);
	cairo_rectangle (cr, x, y, w, h);
	if (ops == EQX_CAIRO_STROKE)
		cairo_stroke (cr);
	else
		cairo_fill (cr);
	cairo_pattern_destroy (pattern);
}
