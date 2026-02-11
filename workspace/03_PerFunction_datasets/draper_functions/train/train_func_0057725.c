get_data_field(const OPDBlock *datablock,
               gdouble pixel_size, gdouble aspect, gdouble wavelength,
               const gchar *zunits,
               GwyDataField **maskfield,
               GError **error)
{
    OPDArrayType datatype;
    GwyDataField *dfield, *mfield;
    GwySIUnit *siunit;
    gdouble *data, *mdata;
    guint xres, yres, mcount;
    const guchar *p;
    guint i, j;

    if (maskfield)
        *maskfield = NULL;

    p = get_array_params(datablock->data, &xres, &yres, &datatype);
    dfield = gwy_data_field_new(xres, yres,
                                xres*pixel_size, aspect*yres*pixel_size, FALSE);

    siunit = gwy_si_unit_new("m");
    gwy_data_field_set_si_unit_xy(dfield, siunit);
    g_object_unref(siunit);

    siunit = gwy_si_unit_new(zunits);
    gwy_data_field_set_si_unit_z(dfield, siunit);
    g_object_unref(siunit);

    mfield = gwy_data_field_new_alike(dfield, FALSE);
    gwy_data_field_fill(mfield, 1.0);

    data = gwy_data_field_get_data(dfield);
    mdata = gwy_data_field_get_data(mfield);
    for (i = 0; i < xres; i++) {
        if (datatype == OPD_ARRAY_FLOAT) {
            for (j = yres; j; j--) {
                gdouble v = gwy_get_gfloat_le(&p);
                if (v < OPD_BAD_FLOAT)
                    data[(j - 1)*xres + i] = wavelength*v;
                else
                    mdata[(j - 1)*xres + i] = 0.0;
            }
        }
        else if (datatype == OPD_ARRAY_INT16) {
            for (j = yres; j; j--) {
                gint v = gwy_get_gint16_le(&p);
                if (v < OPD_BAD_INT16)
                    data[(j - 1)*xres + i] = wavelength*v;
                else
                    mdata[(j - 1)*xres + i] = 0.0;
            }
        }
        else if (datatype == OPD_ARRAY_BYTE) {

            for (j = yres; j; j--) {
                data[(j - 1)*xres + i] = wavelength*(*(p++));
            }
        }
        else {
            err_DATA_TYPE(error, datatype);
            g_object_unref(dfield);
            g_object_unref(mfield);
            return NULL;
        }
    }
    mcount = gwy_app_channel_remove_bad_data(dfield, mfield);

    if (maskfield && mcount)
        *maskfield = mfield;
    else
        g_object_unref(mfield);

    return dfield;
}
