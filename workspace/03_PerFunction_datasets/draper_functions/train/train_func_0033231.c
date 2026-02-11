nodoka_rounded_rectangle (cairo_t * cr,
							  double x, double y, double w, double h,
							  int radius, uint8 corners)
{

	if (radius <= 0)
	{
		cairo_rectangle (cr, x, y, w, h);
		return;
	}

	int r = radius;
	if (w / 2 <= r)
		r = w / 2;
	if (h / 2 <= r)
		r = h / 2;
	if (r < 0)
		r = 0;


	if (corners & NDK_CORNER_TOPLEFT)
		cairo_move_to (cr, x + r, y);
	else
		cairo_move_to (cr, x, y);

	if (corners & NDK_CORNER_TOPRIGHT)
		cairo_arc (cr, x + w - r, y + r, r, M_PI * 1.5,
				   M_PI * 2);
	else
		cairo_line_to (cr, x + w, y);

	if (corners & NDK_CORNER_BOTTOMRIGHT)
		cairo_arc (cr, x + w - r, y + h - r, r, 0, M_PI * 0.5);
	else
		cairo_line_to (cr, x + w, y + h);

	if (corners & NDK_CORNER_BOTTOMLEFT)
		cairo_arc (cr, x + r, y + h - r, r, M_PI * 0.5, M_PI);
	else
		cairo_line_to (cr, x, y + h);

	if (corners & NDK_CORNER_TOPLEFT)
		cairo_arc (cr, x + r, y + r, r, M_PI, M_PI * 1.5);
	else
		cairo_line_to (cr, x, y);
}
