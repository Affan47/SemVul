run_noninteractive(NoiseSynthArgs *args,
                   const GwyDimensionArgs *dimsargs,
                   GwyContainer *data,
                   GwyDataField *dfield,
                   gint oldid,
                   GQuark quark)
{
    GwySIUnit *siunit;
    gboolean replace = dimsargs->replace && dfield;
    gboolean add = dimsargs->add && dfield;
    gint newid;

    if (args->randomize)
        args->seed = g_random_int() & 0x7fffffff;

    if (replace) {

        g_object_ref(dfield);

        gwy_app_undo_qcheckpointv(data, 1, &quark);
        if (!add)
            gwy_data_field_clear(dfield);
    }
    else {
        if (add)
            dfield = gwy_data_field_duplicate(dfield);
        else {
            gdouble mag = pow10(dimsargs->xypow10) * dimsargs->measure;
            dfield = gwy_data_field_new(dimsargs->xres, dimsargs->yres,
                                        mag*dimsargs->xres, mag*dimsargs->yres,
                                        TRUE);

            siunit = gwy_data_field_get_si_unit_xy(dfield);
            gwy_si_unit_set_from_string(siunit, dimsargs->xyunits);

            siunit = gwy_data_field_get_si_unit_z(dfield);
            gwy_si_unit_set_from_string(siunit, dimsargs->zunits);
        }
    }

    noise_synth_do(args, dimsargs, dfield);

    if (replace)
        gwy_data_field_data_changed(dfield);
    else {
        if (data) {
            newid = gwy_app_data_browser_add_data_field(dfield, data, TRUE);
            if (oldid != -1)
                gwy_app_sync_data_items(data, data, oldid, newid, FALSE,
                                        GWY_DATA_ITEM_GRADIENT,
                                        0);
        }
        else {
            newid = 0;
            data = gwy_container_new();
            gwy_container_set_object(data, gwy_app_get_data_key_for_id(newid),
                                     dfield);
            gwy_app_data_browser_add(data);
            gwy_app_data_browser_reset_visibility(data,
                                                  GWY_VISIBILITY_RESET_SHOW_ALL);
            g_object_unref(data);
        }

        gwy_app_set_data_field_title(data, newid, _("Generated"));
    }
    g_object_unref(dfield);
}
