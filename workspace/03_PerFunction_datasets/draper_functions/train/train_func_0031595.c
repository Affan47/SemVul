gwy_data_view_get_pixbuf(GwyDataView *data_view,
                         gint max_width,
                         gint max_height)
{
    GdkPixbuf *pixbuf;
    gint width, height, width_scaled, height_scaled;
    gdouble xscale, yscale, scale;

    g_return_val_if_fail(GWY_IS_DATA_VIEW(data_view), NULL);
    g_return_val_if_fail(data_view->pixbuf, NULL);

    width = gdk_pixbuf_get_width(data_view->pixbuf);
    height = gdk_pixbuf_get_height(data_view->pixbuf);
    xscale = (max_width > 0) ? (gdouble)max_width/width : 1.0;
    yscale = (max_height > 0) ? (gdouble)max_height/height : 1.0;
    scale = MIN(MIN(xscale, yscale), 1.0);
    width_scaled = (gint)(scale*width);
    height_scaled = (gint)(scale*height);
    if (max_width)
        width_scaled = CLAMP(width_scaled, 1, max_width);
    if (max_height)
        height_scaled = CLAMP(height_scaled, 1, max_height);

    pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE,
                            BITS_PER_SAMPLE, width_scaled, height_scaled);
    gwy_debug_objects_creation(G_OBJECT(pixbuf));
    gdk_pixbuf_scale(data_view->pixbuf, pixbuf, 0, 0,
                     width_scaled, height_scaled, 0.0, 0.0,
                     scale, scale, GDK_INTERP_TILES);

    return pixbuf;
}
