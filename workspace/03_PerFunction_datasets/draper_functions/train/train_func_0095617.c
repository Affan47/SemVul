gwy_data_field_grains_remove_by_height(GwyDataField *data_field,
                                       GwyDataField *grain_field,
                                       gdouble threshval,
                                       gboolean below)
{
    gint i, xres, yres, ngrains;
    gdouble *data;
    gboolean *grain_kill;
    gint *grains;

    g_return_if_fail(GWY_IS_DATA_FIELD(data_field));
    g_return_if_fail(GWY_IS_DATA_FIELD(grain_field));

    xres = grain_field->xres;
    yres = grain_field->yres;
    data = grain_field->data;

    threshval = gwy_data_field_get_min(data_field)
                + threshval*(gwy_data_field_get_max(data_field)
                             - gwy_data_field_get_min(data_field))/100.0;

    grains = g_new0(gint, xres*yres);
    ngrains = gwy_data_field_number_grains(grain_field, grains);


    grain_kill = g_new0(gboolean, ngrains + 1);
    if (below) {
        for (i = 0; i < xres*yres; i++) {
            if (grains[i] && data_field->data[i] < threshval)
                grain_kill[grains[i]] = TRUE;
        }
    }
    else {
        for (i = 0; i < xres*yres; i++) {
            if (grains[i] && data_field->data[i] > threshval)
                grain_kill[grains[i]] = TRUE;
        }
    }

    grain_kill[0] = FALSE;


    for (i = 0; i < xres*yres; i++) {
        if (grain_kill[grains[i]])
            data[i] = 0;
    }
    for (i = 1; i <= ngrains; i++) {
        if (grain_kill[i]) {
            gwy_data_field_invalidate(grain_field);
            break;
        }
    }

    g_free(grains);
    g_free(grain_kill);
}
