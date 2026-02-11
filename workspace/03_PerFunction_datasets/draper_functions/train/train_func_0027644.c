validate_item_pass3(gpointer hash_key,
                    gpointer hash_value,
                    gpointer user_data)
{
    GValue *gvalue = (GValue*)hash_value;
    GQuark key = GPOINTER_TO_UINT(hash_key);
    GwyDataValidationInfo *info = (GwyDataValidationInfo*)user_data;
    GSList **errors;
    GObject *object, *child;
    const gchar *typename;
    gint n, i;

    if (!G_VALUE_HOLDS_OBJECT(gvalue))
        return;

    errors = &info->errors;
    object = g_value_get_object(gvalue);
    typename = G_OBJECT_TYPE_NAME(object);

    check_ref_count(object, key, info->stack, errors);

    PUSH(info->stack, typename);
    if (GWY_IS_CONTAINER(object)) {
        gwy_container_foreach((GwyContainer*)object, NULL,
                              &validate_item_pass3, info);
    }
    else if (GWY_IS_DATA_FIELD(object)) {
        GwyDataField *data_field = (GwyDataField*)object;

        CRFC(data_field->si_unit_xy, "si-unit-xy");
        CRFC(data_field->si_unit_z, "si-unit-z");
    }
    else if (GWY_IS_DATA_LINE(object)) {
        GwyDataLine *data_line = (GwyDataLine*)object;

        CRFC(data_line->si_unit_x, "si-unit-x");
        CRFC(data_line->si_unit_y, "si-unit-y");
    }
    else if (GWY_IS_GRAPH_MODEL(object)) {
        GwyGraphModel *graph_model = (GwyGraphModel*)object;

        CRFC(graph_model->x_unit, "si-unit-x");
        CRFC(graph_model->y_unit, "si-unit-y");

        PUSH(info->stack, "curve");
        n = gwy_graph_model_get_n_curves(graph_model);
        for (i = 0; i < n; i++) {
            child = (GObject*)gwy_graph_model_get_curve(graph_model, i);
            check_ref_count(child, key, info->stack, errors);
        }
        POP(info->stack);
    }
    else if (GWY_IS_SPECTRA(object)) {
        GwySpectra *spectra = (GwySpectra*)object;

        CRFC(spectra->si_unit_xy, "si-unit-xy");

        PUSH(info->stack, "spectrum");
        n = gwy_spectra_get_n_spectra(spectra);
        for (i = 0; i < n; i++) {
            GwyDataLine *data_line = gwy_spectra_get_spectrum(spectra, i);

            CRFC(data_line->si_unit_x, "si-unit-x");
            CRFC(data_line->si_unit_y, "si-unit-y");
        }
        POP(info->stack);
    }
    POP(info->stack);
}
