drawLine(const std::vector<point>& coords,
                              const rgba& color, const SWFMatrix& mat)
{
    if (coords.empty()) return;

    CairoScopeMatrix mat_transformer(_cr, mat);

    std::vector<point>::const_iterator i = coords.begin();

    double x = i->x, y = i->y;
    snap_to_half_pixel(_cr, x, y);

    cairo_move_to(_cr, x, y);

    for (std::vector<point>::const_iterator e = coords.end(); i != e; ++i) {
        double x = i->x, y = i->y;
        snap_to_half_pixel(_cr, x, y);
        cairo_line_to(_cr, x, y);
    }

    set_color(color);
    cairo_set_line_cap(_cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_join(_cr, CAIRO_LINE_JOIN_ROUND);

    double hwidth = 1.0;

    cairo_device_to_user_distance(_cr, &hwidth, &hwidth);
    cairo_set_line_width(_cr, hwidth);

    cairo_stroke(_cr);
}
