gwy_pixbuf_draw_data_field_with_range(GdkPixbuf *pixbuf,
                                      GwyDataField *data_field,
                                      GwyGradient *gradient,
                                      gdouble minimum,
                                      gdouble maximum)
{
    int xres, yres, i, j, palsize, rowstride, dval;
    guchar *pixels, *line;
    const guchar *samples, *s;
    gdouble cor;
    const gdouble *row, *data;

    g_return_if_fail(GDK_IS_PIXBUF(pixbuf));
    g_return_if_fail(GWY_IS_DATA_FIELD(data_field));
    g_return_if_fail(GWY_IS_GRADIENT(gradient));
    if (minimum == maximum)
        maximum = G_MAXDOUBLE;

    xres = gwy_data_field_get_xres(data_field);
    yres = gwy_data_field_get_yres(data_field);
    data = gwy_data_field_get_data_const(data_field);

    g_return_if_fail(xres == gdk_pixbuf_get_width(pixbuf));
    g_return_if_fail(yres == gdk_pixbuf_get_height(pixbuf));

    pixels = gdk_pixbuf_get_pixels(pixbuf);
    rowstride = gdk_pixbuf_get_rowstride(pixbuf);
    samples = gwy_gradient_get_samples(gradient, &palsize);
    cor = (palsize-1.0)/(maximum-minimum);

    for (i = 0; i < yres; i++) {
        line = pixels + i*rowstride;
        row = data + i*xres;
        for (j = 0; j < xres; j++) {
            dval = (gint)((*(row++) - minimum)*cor + 0.5);
            dval = GWY_CLAMP(dval, 0, palsize-1);


            s = samples + 4*dval;
            *(line++) = *(s++);
            *(line++) = *(s++);
            *(line++) = *s;
        }
    }
}
