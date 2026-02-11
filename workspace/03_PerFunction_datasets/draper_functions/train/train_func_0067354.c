read_data_field(gconstpointer p,
                gint xres, gint yres,
                guint bpp,
                GwyDataField **maskfield)
{
    GwyDataField *dfield, *mfield;
    GwySIUnit *unit;
    gdouble *data, *mdata;
    gint i, j, mcount;

    if (maskfield)
        *maskfield = NULL;

    dfield = gwy_data_field_new(xres, yres, 1.0, 1.0, FALSE);
    unit = gwy_si_unit_new("m");
    gwy_data_field_set_si_unit_xy(dfield, unit);
    g_object_unref(unit);
    unit = gwy_si_unit_new("m");
    gwy_data_field_set_si_unit_z(dfield, unit);
    g_object_unref(unit);

    mfield = gwy_data_field_new_alike(dfield, FALSE);
    gwy_data_field_fill(mfield, 1.0);

    data = gwy_data_field_get_data(dfield);
    mdata = gwy_data_field_get_data(mfield);
    if (bpp == 4) {
        const guint32 *d32 = p;
        for (i = 0; i < yres; i++) {
            for (j = 0; j < xres; j++) {
                gint32 v = GINT32_FROM_LE(*d32);
                if (v != G_MAXINT32)
                    data[i*xres + j] = v/(gdouble)G_MAXINT32/5.625e4;
                else
                    mdata[i*xres + j] = 0.0;
                d32++;
            }
        }
    }
    else if (bpp == 2) {
        const guint16 *d16 = p;
        for (i = 0; i < yres; i++) {
            for (j = 0; j < xres; j++) {
                gint16 v = GINT16_FROM_LE(*d16);


                if (v != G_MAXINT16)
                    data[i*xres + j] = v/(gdouble)G_MAXINT16/5.625e4/7.61;
                else
                    mdata[i*xres + j] = 0.0;
                d16++;
            }
        }
    }

    mcount = gwy_app_channel_remove_bad_data(dfield, mfield);

    if (maskfield && mcount)
        *maskfield = mfield;
    else
        g_object_unref(mfield);

    return dfield;
}
