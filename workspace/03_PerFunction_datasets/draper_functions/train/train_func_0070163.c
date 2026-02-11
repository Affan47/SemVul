scale(int w, int h) {
    ref<YImage> image;
    GdkPixbuf *pixbuf = 0;
    bool alpha = gdk_pixbuf_get_has_alpha(fPixbuf);
#if 0
    pixbuf = gdk_pixbuf_scale_simple(fPixbuf,
                                     w, h,
                                     GDK_INTERP_BILINEAR);
#else
    pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, alpha, 8, w, h);

    pixbuf_scale(gdk_pixbuf_get_pixels(fPixbuf),
                 gdk_pixbuf_get_rowstride(fPixbuf),
                 gdk_pixbuf_get_width(fPixbuf),
                 gdk_pixbuf_get_height(fPixbuf),
                 gdk_pixbuf_get_pixels(pixbuf),
                 gdk_pixbuf_get_rowstride(pixbuf),
                 gdk_pixbuf_get_width(pixbuf),
                 gdk_pixbuf_get_height(pixbuf),
                 alpha);
#endif

    if (pixbuf != NULL) {
        image.init(new YImageGDK(w, h, pixbuf));
    }

    return image;
}
