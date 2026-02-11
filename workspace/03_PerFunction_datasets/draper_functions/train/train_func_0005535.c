dither_pixbuf(GdkPixbuf * dest, GdkPixbuf * src)
{
    gint y;
    guchar *ibuf, *obuf;
    gint irowstride, orowstride;
    gint width, height;
    gint alpha;

    rgb_preprocess_dm_565();

    ibuf = gdk_pixbuf_get_pixels(src);
    obuf = gdk_pixbuf_get_pixels(dest);

    irowstride = gdk_pixbuf_get_rowstride(src);
    orowstride = gdk_pixbuf_get_rowstride(dest);

    width = gdk_pixbuf_get_width(src);
    height = gdk_pixbuf_get_height(src);

    alpha = gdk_pixbuf_get_has_alpha(src);

    for (y = 0; y < height; y++) {
        dither_line(y, obuf, ibuf, width, alpha);
        ibuf += irowstride;
        obuf += orowstride;
    }
}
