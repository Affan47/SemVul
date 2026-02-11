gwy_tool_read_value_set_zero(GwyToolReadValue *tool)
{
    GwyPlainTool *plain_tool;
    GQuark quark;

    plain_tool = GWY_PLAIN_TOOL(tool);
    if (!plain_tool->data_field
        || !gwy_selection_get_data(plain_tool->selection, NULL)
        || !tool->avg)
        return;

    quark = gwy_app_get_data_key_for_id(plain_tool->id);
    gwy_app_undo_qcheckpointv(plain_tool->container, 1, &quark);
    gwy_data_field_add(plain_tool->data_field, -tool->avg);
    gwy_data_field_data_changed(plain_tool->data_field);
}
