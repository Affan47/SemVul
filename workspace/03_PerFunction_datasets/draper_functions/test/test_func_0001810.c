create_colorwheel_hs_pixbuf (gint diameter) {
    GdkPixbuf * colorwheel = NULL;
    gint width, height, rowstride;
    float angle, percent_radius;
    HSV hsv;
    guchar * data;
    gint x, y, draw_x, draw_y, p, xcenter, ycenter;

    hsv.V = 1;
    width = height = diameter;
    xcenter = width / 2;
    ycenter = height / 2;
    diameter -= 2;

    colorwheel = gdk_pixbuf_new  (GDK_COLORSPACE_RGB,
                                  TRUE,
                                  8,
                                  width, height);
    data = gdk_pixbuf_get_pixels (colorwheel);
    rowstride = gdk_pixbuf_get_rowstride(colorwheel);

    x = 0;
    y = diameter/2;
    p = 3 - 2*diameter/2;

    while (x <= y) {
        draw_y = y;
        for (draw_x = x; draw_x >= -x; draw_x--) {
            percent_radius = (2.0 * sqrt (draw_x*draw_x + draw_y*draw_y)) /
                ((float) diameter);
            angle = atan2((double) draw_y, (double) draw_x);
            colorwheel_plot_point(data, hsv, percent_radius, angle,
                                  rowstride,
                                  draw_x + xcenter, draw_y + ycenter);
        }

        draw_y = -y;
        for (draw_x = x; draw_x >= -x; draw_x--) {
            percent_radius = (2.0 * sqrt (draw_x*draw_x + draw_y*draw_y)) /
                ((float) diameter);
            angle = atan2((double) draw_y, (double) draw_x);
            colorwheel_plot_point(data, hsv, percent_radius, angle, rowstride,
                                  draw_x + xcenter, draw_y + ycenter);
        }

        draw_y = x;
        for (draw_x = y; draw_x >= -y; draw_x--) {
            percent_radius = (2.0 * sqrt (draw_x*draw_x + draw_y*draw_y)) /
                ((float) diameter);
            angle = atan2((double) draw_y, (double) draw_x);
            colorwheel_plot_point(data, hsv, percent_radius, angle, rowstride,
                                  draw_x + xcenter, draw_y + ycenter);
        }

        draw_y = -x;
        for (draw_x = y; draw_x >= -y; draw_x--) {
            percent_radius = (2.0 * sqrt (draw_x*draw_x + draw_y*draw_y)) /
                ((float) diameter);
            angle = atan2((double) draw_y, (double) draw_x);
            colorwheel_plot_point(data, hsv, percent_radius, angle, rowstride,
                                  draw_x + xcenter, draw_y + ycenter);
        }
        if (p < 0)
            p += 4 * x++ + 6;
        else
            p += 4 * (x++ - y--) + 10;
    }
    return colorwheel;
}
