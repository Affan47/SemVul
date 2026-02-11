draw_frame (GdkPixbuf *diff, gint sub_width, gint sub_height,
            guchar red, guchar green, guchar blue, guchar alpha)
{
    guchar *pixels;
    gint n_channels, row_stride, width, height;
    gint x, y, i, channel;
    guchar pixel[4];
    gint xes[3], yes[3];

    pixel[0] = red;
    pixel[1] = green;
    pixel[2] = blue;
    pixel[3] = alpha;

    xes[0] = 0;
    xes[1] = sub_width + 1;
    xes[2] = sub_width * 2 + 2;

    yes[0] = 0;
    yes[1] = sub_height + 1;
    yes[2] = sub_height * 2 + 2;

    n_channels = gdk_pixbuf_get_n_channels(diff);
    row_stride = gdk_pixbuf_get_rowstride(diff);
    width = gdk_pixbuf_get_width(diff);
    height = gdk_pixbuf_get_height(diff);
    pixels = gdk_pixbuf_get_pixels(diff);

    for (y = 0; y < height; y++) {
        for (i = 0; i < sizeof(xes) / sizeof(*xes); i++) {
            guchar *target_pixel;

            target_pixel = pixels + xes[i] * n_channels + y * row_stride;
            for (channel = 0; channel < n_channels; channel++) {
                target_pixel[channel] = pixel[channel];
            }
        }
    }

    for (x = 0; x < width; x++) {
        for (i = 0; i < sizeof(yes) / sizeof(*yes); i++) {
            guchar *target_pixel;

            target_pixel = pixels + x * n_channels + yes[i] * row_stride;
            for (channel = 0; channel < n_channels; channel++) {
                target_pixel[channel] = pixel[channel];
            }
        }
    }
}
