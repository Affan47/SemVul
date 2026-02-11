preview(DriftControls *controls,
        DriftArgs *args)
{
    GwyDataField *mask, *dfield;

    dfield = GWY_DATA_FIELD(gwy_container_get_object_by_name(controls->mydata,
                                                             "/0/data"));

    if (!gwy_container_gis_object_by_name(controls->mydata, "/0/mask", &mask)) {
        mask = create_mask_field(dfield);
        gwy_container_set_object_by_name(controls->mydata, "/0/mask", mask);
        g_object_unref(mask);
    }

    gwy_app_wait_cursor_start(GTK_WINDOW(controls->dialog));
    if (!controls->result) {
        controls->result = gwy_data_field_duplicate(dfield);
        gwy_container_set_object_by_name(controls->mydata, "/1/data",
                                         controls->result);
        controls->drift = gwy_data_line_new(1, 1.0, FALSE);
    }
    else
        gwy_data_field_copy(dfield, controls->result, FALSE);
    drift_do(args, dfield, controls->result, controls->drift);
    gwy_data_field_data_changed(controls->result);
    mask_process(mask, controls->drift);
    gwy_app_wait_cursor_finish(GTK_WINDOW(controls->dialog));

    controls->computed = TRUE;
}
