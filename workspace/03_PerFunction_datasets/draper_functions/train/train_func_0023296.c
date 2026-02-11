tip_update(TipBlindControls *controls)
{
    GwyDataField *vtipfield, *tipfield, *buffer;
    TipBlindArgs *args = controls->args;
    GtkAdjustment *adj = GTK_ADJUSTMENT(controls->stripeno);
    guint stripeno;

    tipfield = controls->tip;
    stripeno = gwy_adjustment_get_int(adj);
    if (args->split_to_stripes && args->stripetips
        && stripeno > 0 && stripeno <= controls->oldnstripes
        && args->stripetips[stripeno]) {
        tipfield = args->stripetips[stripeno-1];
    }

    buffer = gwy_data_field_duplicate(tipfield);
    gwy_data_field_resample(buffer, controls->vxres, controls->vyres,
                            GWY_INTERPOLATION_ROUND);

    vtipfield = GWY_DATA_FIELD(gwy_container_get_object_by_name(controls->vtip,
                                                                "/0/data"));

    gwy_data_field_copy(buffer, vtipfield, FALSE);
    g_object_unref(buffer);
    gwy_data_field_data_changed(vtipfield);
}
