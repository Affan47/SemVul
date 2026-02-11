draw_waves (cairo_t *cr,
            double   cx,
            double   cy,
            double   max_radius,
            int      volume_level)
{
        const int n_waves = 3;
        int last_wave;
        int i;

        last_wave = n_waves * volume_level / 100;

        for (i = 0; i < n_waves; i++) {
                double angle1;
                double angle2;
                double radius;
                double alpha;

                angle1 = -M_PI / 4;
                angle2 = M_PI / 4;

                if (i < last_wave)
                        alpha = 1.0;
                else if (i > last_wave)
                        alpha = 0.1;
                else alpha = 0.1 + 0.9 * (n_waves * volume_level % 100) / 100.0;

                radius = (i + 1) * (max_radius / n_waves);
                cairo_arc (cr, cx, cy, radius, angle1, angle2);
                cairo_set_source_rgba (cr, 0.6, 0.6, 0.6, alpha / 2);
                cairo_set_line_width (cr, 14);
                cairo_set_line_cap  (cr, CAIRO_LINE_CAP_ROUND);
                cairo_stroke_preserve (cr);

                cairo_set_source_rgba (cr, 1.0, 1.0, 1.0, alpha);
                cairo_set_line_width (cr, 10);
                cairo_set_line_cap  (cr, CAIRO_LINE_CAP_ROUND);
                cairo_stroke (cr);
        }
}
