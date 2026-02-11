_cairo_rectangle_partial (cairo_t *cr,
			  double   x,
			  double   y,
			  double   w,
			  double   h,
			  Sides    sides)
{
	if (sides & SIDE_TOP) {
		cairo_move_to (cr, x, y);
		cairo_rel_line_to (cr, w, 0);
	}

	if (sides & SIDE_RIGHT) {
		cairo_move_to (cr, x + w, y);
		cairo_rel_line_to (cr, 0, h);
	}

	if (sides & SIDE_BOTTOM) {
		cairo_move_to (cr, x, y + h);
		cairo_rel_line_to (cr, w, 0);
	}

	if (sides & SIDE_LEFT) {
		cairo_move_to (cr, x, y);
		cairo_rel_line_to (cr, 0, h);
	}
}
