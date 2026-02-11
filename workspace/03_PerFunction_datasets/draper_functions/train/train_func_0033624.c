grain_wshed(GwyContainer *data, GwyRunType run)
{
    WshedArgs args;
    GwyDataField *dfield;
    GQuark mquark;
    gint id;

    g_return_if_fail(run & WSHED_RUN_MODES);
    wshed_load_args(gwy_app_settings_get(), &args);
    gwy_app_data_browser_get_current(GWY_APP_DATA_FIELD, &dfield,
                                     GWY_APP_DATA_FIELD_ID, &id,
                                     GWY_APP_MASK_FIELD_KEY, &mquark,
                                     0);
    g_return_if_fail(dfield && mquark);

    if (run == GWY_RUN_IMMEDIATE)
        run_noninteractive(&args, data, dfield, mquark, id);
    else {
        wshed_dialog(&args, data, dfield, id, mquark);
        wshed_save_args(gwy_app_settings_get(), &args);
    }
}
