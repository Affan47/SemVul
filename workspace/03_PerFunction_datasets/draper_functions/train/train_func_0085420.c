gwy_data_field_elliptic_area_unextract(GwyDataField *data_field,
                                       gint col, gint row,
                                       gint width, gint height,
                                       const gdouble *data)
{
    gint i, from, to, xres, count;
    gdouble a, b, s;
    gdouble *d;

    g_return_if_fail(GWY_IS_DATA_FIELD(data_field));
    g_return_if_fail(col >= 0 && row >= 0
                     && width >= 0 && height >= 0
                     && col + width <= data_field->xres
                     && row + height <= data_field->yres);

    a = width/2.0;
    b = height/2.0;
    xres = data_field->xres;
    count = 0;

    for (i = 0; i < height; i++) {
        d = data_field->data + (row + i)*xres + col;
        s = (i + 0.5)/b;
        s = s*(2.0 - s);
        if (G_UNLIKELY(s <= 0.0))
            continue;
        s = sqrt(s);
        from = ceil(a*(1.0 - s) - 0.5);
        to = floor(a*(1.0 + s) - 0.5);
        if (G_UNLIKELY(from < 0))
            from = 0;
        if (G_UNLIKELY(to >= width))
            to = width-1;
        if (G_LIKELY(to >= from)) {
            memcpy(d + from, data + count, (to - from + 1)*sizeof(gdouble));
            count += to - from + 1;
        }
    }

    gwy_data_field_invalidate(data_field);
}
