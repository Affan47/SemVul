gwy_data_field_area_filter_conservative(GwyDataField *data_field,
                                        gint size,
                                        gint col, gint row,
                                        gint width, gint height)
{
    gint xres, yres, i, j, ii, jj;
    gdouble maxval, minval;
    gdouble *data;
    GwyDataField *hlp_df;

    gwy_debug("");
    g_return_if_fail(GWY_IS_DATA_FIELD(data_field));
    g_return_if_fail(size > 0);
    xres = data_field->xres;
    yres = data_field->yres;
    g_return_if_fail(col >= 0 && row >= 0
                     && width > 0 && height > 0
                     && col + width <= xres
                     && row + height <= yres);
    if (size == 1)
        return;
    if (size > width || size > height) {
        g_warning("Kernel size larger than field area size.");
        return;
    }

    hlp_df = gwy_data_field_new(width, height, 1.0, 1.0, FALSE);

    data = data_field->data;
    for (i = 0; i < height; i++) {
        gint ifrom = MAX(0, i + row - (size-1)/2);
        gint ito = MIN(yres-1, i + row + size/2);

        for (j = 0; j < width; j++) {
            gint jfrom = MAX(0, j + col - (size-1)/2);
            gint jto = MIN(xres-1, j + col + size/2);

            maxval = -G_MAXDOUBLE;
            minval = G_MAXDOUBLE;
            for (ii = 0; ii <= ito - ifrom; ii++) {
                gdouble *drow = data + (ifrom + ii)*xres + jfrom;

                for (jj = 0; jj <= jto - jfrom; jj++) {
                    if (i + row == ii + ifrom && j + col == jj + jfrom)
                        continue;

                    if (drow[jj] < minval)
                        minval = drow[jj];
                    if (drow[jj] > maxval)
                        maxval = drow[jj];
                }
            }

            hlp_df->data[i*width + j] = CLAMP(data[(i + row)*xres + j + col],
                                              minval, maxval);
        }
    }

    if (size == 2)
        hlp_df->data[height*width - 1] = data[(row + height - 1)*xres
                                              + col + width - 1];

    gwy_data_field_area_copy(hlp_df, data_field, 0, 0, width, height, col, row);
    g_object_unref(hlp_df);
    gwy_data_field_invalidate(data_field);
}
