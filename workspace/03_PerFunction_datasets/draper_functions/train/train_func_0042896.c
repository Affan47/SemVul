gwy_data_field_filter_prewitt_total(GwyDataField *data_field)
{
    GwyDataField *workspace;
    g_return_if_fail(GWY_IS_DATA_FIELD(data_field));
    workspace = gwy_data_field_duplicate(data_field);
    gwy_data_field_area_filter_prewitt(data_field, GWY_ORIENTATION_HORIZONTAL,
                                       0, 0,
                                       data_field->xres, data_field->yres);
    gwy_data_field_area_filter_prewitt(workspace, GWY_ORIENTATION_VERTICAL,
                                       0, 0,
                                       data_field->xres, data_field->yres);
    gwy_data_field_hypot_of_fields(data_field, data_field, workspace);
    g_object_unref(workspace);
}
