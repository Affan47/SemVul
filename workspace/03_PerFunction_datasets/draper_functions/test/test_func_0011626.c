flip_xy(GwyDataField *source, GwyDataField *dest, gboolean minor)
{
    gint xres, yres, i, j;
    gdouble *dd;
    const gdouble *sd;

    xres = gwy_data_field_get_xres(source);
    yres = gwy_data_field_get_yres(source);
    gwy_data_field_resample(dest, yres, xres, GWY_INTERPOLATION_NONE);
    sd = gwy_data_field_get_data_const(source);
    dd = gwy_data_field_get_data(dest);
    if (minor) {
        for (i = 0; i < xres; i++) {
            for (j = 0; j < yres; j++) {
                dd[i*yres + j] = sd[j*xres + (xres - 1 - i)];
            }
        }
    }
    else {
        for (i = 0; i < xres; i++) {
            for (j = 0; j < yres; j++) {
                dd[i*yres + (yres - 1 - j)] = sd[j*xres + i];
            }
        }
    }
    gwy_data_field_set_xreal(dest, gwy_data_field_get_yreal(source));
    gwy_data_field_set_yreal(dest, gwy_data_field_get_xreal(source));
}
