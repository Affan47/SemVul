oldmda_read_data(OldMDAFile *mdafile, const gchar *buffer)
{
    GwyBrick *brick;
    GwyDataField *dfield;
    GwyDataLine *cal;
    gdouble *data;
    gint i, j, k;
    const guchar *p;

    p = buffer;
    brick = gwy_brick_new(mdafile->xres, mdafile->yres, mdafile->zres,
                          mdafile->xreal, mdafile->yreal, mdafile->zres,
                          TRUE);
    data = gwy_brick_get_data(brick);

    for (k = 0; k < mdafile->zres; k++) {
        p = buffer + k * 4;
        for (i = 0; i < mdafile->yres; i++)
            for (j = 0; j < mdafile->xres; j++) {
                *(data + k * mdafile->xres * mdafile->yres + j
                    + (mdafile->yres - i - 1) * mdafile->xres)
                        = (gdouble)gwy_get_gint32_le(&p);
                p += (mdafile->zres - 1) * 4;
            }
    }

    gwy_brick_set_si_unit_x(brick, mdafile->siunitx);
    gwy_brick_set_si_unit_y(brick, mdafile->siunity);
    gwy_brick_set_si_unit_z(brick, mdafile->siunitz);

    cal = gwy_data_line_new(mdafile->zres, mdafile->zres, FALSE);
    data = gwy_data_line_get_data(cal);
    for (k = 0; k < mdafile->zres; k++) {
        *(data++) = g_array_index(mdafile->xdata, gdouble, k);
    }
    gwy_data_line_set_si_unit_y(cal, mdafile->siunitz);
    gwy_brick_set_zcalibration(brick, cal);
    g_object_unref(cal);

    g_object_unref(mdafile->siunitx);
    g_object_unref(mdafile->siunity);
    g_object_unref(mdafile->siunitz);

    dfield = gwy_data_field_new(mdafile->xres, mdafile->yres,
                                mdafile->xreal, mdafile->yreal,
                                TRUE);
    gwy_container_set_object_by_name(mdafile->data, "/brick/0", brick);
    gwy_container_set_string_by_name(mdafile->data, "/brick/0/title",
                                     g_strdup("MDA data"));
    gwy_brick_mean_plane(brick, dfield, 0, 0, 0,
                         mdafile->xres, mdafile->yres, -1, FALSE);
    gwy_container_set_object_by_name(mdafile->data, "/brick/0/preview",
                                     dfield);
    g_object_unref(dfield);
    g_object_unref(brick);
}
