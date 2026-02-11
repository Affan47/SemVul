fft_synth(GwyContainer *data, GwyRunType run)
{
    FFTSynthArgs args;
    GwyDimensionArgs dimsargs;
    GwyDataField *dfield;
    GQuark quark;
    gint id;

    g_return_if_fail(run & FFT_SYNTH_RUN_MODES);
    fft_synth_load_args(gwy_app_settings_get(), &args, &dimsargs);
    gwy_app_data_browser_get_current(GWY_APP_DATA_FIELD, &dfield,
                                     GWY_APP_DATA_FIELD_ID, &id,
                                     GWY_APP_DATA_FIELD_KEY, &quark,
                                     0);

    if (run == GWY_RUN_IMMEDIATE
        || fft_synth_dialog(&args, &dimsargs, data, dfield, id))
        run_noninteractive(&args, &dimsargs, data, dfield, id, quark);

    if (run == GWY_RUN_INTERACTIVE)
        fft_synth_save_args(gwy_app_settings_get(), &args, &dimsargs);

    gwy_dimensions_free_args(&dimsargs);
}
