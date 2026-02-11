gwy_data_field_area_hconvolve(GwyDataField *data_field,
                              GwyDataLine *kernel_line,
                              gint col, gint row,
                              gint width, gint height)
{
    gint kres, mres, k0, i, j, k, pos;
    const gdouble *kernel;
    gdouble *buf, *drow;
    gdouble d;

    kres = kernel_line->res;
    kernel = kernel_line->data;
    mres = 2*width;
    k0 = (kres/2 + 1)*mres;
    buf = g_new(gdouble, kres);

    for (i = 0; i < height; i++) {
        drow = data_field->data + (row + i)*data_field->xres + col;

        gwy_clear(buf, kres);
        for (j = 0; j < kres; j++) {
            k = (j - kres/2 + k0) % mres;
            d = drow[k < width ? k : mres-1 - k];
            for (k = 0; k <= j; k++)
                buf[k] += kernel[j - k]*d;
        }
        pos = 0;


        for (j = 0; j < width; j++) {
            drow[j] = buf[pos];
            buf[pos] = 0.0;
            pos = (pos + 1) % kres;
            k = (j + kres - kres/2 + k0) % mres;
            d = drow[G_LIKELY(k < width) ? k : mres-1 - k];
            for (k = pos; k < kres; k++)
                buf[k] += kernel[kres-1 - (k - pos)]*d;
            for (k = 0; k < pos; k++)
                buf[k] += kernel[pos-1 - k]*d;
        }
    }

    g_free(buf);
}
