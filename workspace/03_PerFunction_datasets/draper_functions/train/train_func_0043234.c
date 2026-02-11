xfce_draw_grip_slide (GtkStyle * style, GdkWindow * window, GtkStateType state_type, GdkRectangle * area, GtkWidget * widget, gint x, gint y, gint width, gint height, GtkOrientation orientation)
{
    gint gx, gy, gwidth, gheight;
    cairo_t *cr;
    GdkColor *light, *dark, *mid, *bg;

    light = &style->light[state_type];
    dark = &style->dark[state_type];
    mid = &style->mid[state_type];
    bg = &style->base[GTK_STATE_SELECTED];

    gx = gy = gwidth = gheight = 0;

    if (orientation == GTK_ORIENTATION_HORIZONTAL)
    {
        gint delta = ((gint)((height - 3) / 2));
        gx = x + delta;
        gy = y + delta;
        gwidth = width - 2 * delta - 1;
        gheight = height - 2 * delta - 1;
    }
    else
    {
        gint delta = ((gint)((width - 3) / 2));
        gx = x + delta;
        gy = y + delta;
        gwidth = width - 2 * delta - 1;
        gheight = height - 2 * delta - 1;
    }

    cr = ge_gdk_drawable_to_cairo(window, area);

    if ((gheight > 1) && (gwidth > 1))
    {
        gdk_cairo_set_source_color(cr, bg);
        cairo_rectangle(cr, gx + 1, gy + 1, gwidth - 1, gheight - 1);
        cairo_fill(cr);

        gdk_cairo_set_source_color(cr, dark);
        cairo_move_to(cr, gx + 0.5, gy + gheight + 0.5);
        cairo_line_to(cr, gx + 0.5, gy + 0.5);
        cairo_line_to(cr, gx + gwidth + 0.5, gy + 0.5);
        cairo_stroke(cr);

        gdk_cairo_set_source_color(cr, light);
        cairo_move_to(cr, gx + 0.5, gy + gheight + 0.5);
        cairo_line_to(cr, gx + gwidth + 0.5, gy + gheight + 0.5);
        cairo_line_to(cr, gx + gwidth + 0.5, gy + 0.5);
        cairo_stroke(cr);

        gdk_cairo_set_source_color(cr, mid);
        cairo_rectangle(cr, gx, gy, 1, 1);
        cairo_rectangle(cr, gx + gwidth, gy, 1, 1);
        cairo_rectangle(cr, gx, gy + gheight, 1, 1);
        cairo_rectangle(cr, gx + gwidth, gy + gheight, 1, 1);
        cairo_fill(cr);
    }

    cairo_destroy(cr);
}
