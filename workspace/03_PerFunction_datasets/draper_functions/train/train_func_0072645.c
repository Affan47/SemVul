_cairo_draw_rounded_box (cairo_t *cr,
			 double   x,
			 double   y,
			 double   w,
			 double   h,
			 double   r)
{
	if (r == 0) {
		cairo_rectangle (cr, x, y, w, h);
	}
	else {
		cairo_move_to (cr, x, y + r);
		if (r > 0)
			cairo_arc (cr, x + r, y + r, r, 1.0 * M_PI, 1.5 * M_PI);
		cairo_rel_line_to (cr, w - (r * 2), 0);
		if (r > 0)
			cairo_arc (cr, x + w - r, y + r, r, 1.5 * M_PI, 2.0 * M_PI);
		cairo_rel_line_to (cr, 0, h - (r * 2));
		if (r > 0)
			cairo_arc (cr, x + w - r, y + h - r, r, 0.0 * M_PI, 0.5 * M_PI);
		cairo_rel_line_to (cr, - (w - (r * 2)), 0);
		if (r > 0)
			cairo_arc (cr, x + r, y + h - r, r, 0.5 * M_PI, 1.0 * M_PI);
		cairo_rel_line_to (cr, 0, - (h - (r * 2)));
	}
}
