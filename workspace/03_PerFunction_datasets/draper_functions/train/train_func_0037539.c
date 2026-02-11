facets_analyse(GwyContainer *data, GwyRunType run)
{
    FacetsArgs args;
    GwyContainer *fdata;
    GwyDataField *dfield, *mfield;
    GQuark mquark;
    gint id;

    g_return_if_fail(run & FACETS_RUN_MODES);
    g_return_if_fail(g_type_from_name("GwyLayerPoint"));
    facets_load_args(gwy_app_settings_get(), &args);

    gwy_app_data_browser_get_current(GWY_APP_DATA_FIELD, &dfield,
                                     GWY_APP_MASK_FIELD_KEY, &mquark,
                                     GWY_APP_MASK_FIELD, &mfield,
                                     GWY_APP_DATA_FIELD_ID, &id,
                                     0);
    g_return_if_fail(dfield && mquark);

    fdata = gwy_container_new();
    gwy_data_field_facet_distribution(dfield, 2*args.kernel_size + 1, fdata);
    args.theta0 = gwy_container_get_double_by_name(fdata, "/theta0");
    args.phi0 = gwy_container_get_double_by_name(fdata, "/phi0");
    if (run == GWY_RUN_IMMEDIATE)
        run_noninteractive(&args, data, fdata, dfield, mfield, mquark);
    else {
        facets_dialog(&args, data, fdata, dfield, mfield, id, mquark);
        facets_save_args(gwy_app_settings_get(), &args);
    }
    g_object_unref(fdata);
}
