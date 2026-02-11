compensate_drift(GwyContainer *data, GwyRunType run)
{
    DriftArgs args;
    GwyDataField *dfield, *mfield, *sfield;
    gint id;

    g_return_if_fail(run & DRIFT_RUN_MODES);
    drift_load_args(gwy_app_settings_get(), &args);
    gwy_app_data_browser_get_current(GWY_APP_DATA_FIELD, &dfield,
                                     GWY_APP_MASK_FIELD, &mfield,
                                     GWY_APP_SHOW_FIELD, &sfield,
                                     GWY_APP_DATA_FIELD_ID, &id,
                                     0);
    g_return_if_fail(dfield);

    if (run == GWY_RUN_IMMEDIATE)
        run_noninteractive(&args, data, dfield, mfield, sfield, NULL, NULL, id);
    else {
        drift_dialog(&args, data, dfield, mfield, sfield, id);
        drift_save_args(gwy_app_settings_get(), &args);
    }
}
