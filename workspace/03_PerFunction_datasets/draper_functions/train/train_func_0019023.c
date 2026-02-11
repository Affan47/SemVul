Draw (cairo_t *cr, G_GNUC_UNUSED bool is_vector) const
{
	GOColor color = GetEffectiveLineColor ();
	if (color != 0) {
		double dx = m_xend - m_xstart, dy = m_yend - m_ystart, length = sqrt (dx * dx + dy * dy);
		dx /= length;
		dy /= length;

		int n = floor (length / m_Step);

		length /= n;
		double xstep = length * dx, ystep = length * dy, x = xstep / 1.5, y = ystep / 1.5;

		double width = m_Width / 2. - GetLineWidth () / 2.;
		double x0 = m_xstart + dy * width + xstep / 2.,
			   y0 = m_ystart - dx * width + ystep / 2.,
			   x1 = m_xstart - dy * width + 1.5 * xstep,
			   y1 = m_ystart + dx * width + 1.5 * ystep, t;
		cairo_set_line_width (cr, GetLineWidth ());
		cairo_set_line_cap (cr, CAIRO_LINE_CAP_BUTT);
		cairo_move_to (cr, m_xstart, m_ystart);
		cairo_curve_to (cr, m_xstart + x, m_ystart + y, x0 - x, y0 - y, x0, y0);
		for (int i = 1; i < n; i++) {
			cairo_curve_to (cr, x0 + x, y0 + y, x1 - x, y1 - y, x1, y1);
			t = x0;
			x0 = x1;
			x1 = t + 2 * xstep;
			t = y0;
			y0 = y1;
			y1 = t + 2 * ystep;
		}
		cairo_curve_to (cr, x0 + x, y0 + y, m_xend - x, m_yend - y, m_xend, m_yend);
		cairo_set_source_rgba (cr, GO_COLOR_TO_CAIRO (color));
		cairo_stroke (cr);
	}
}
