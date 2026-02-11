gwy_tool_read_value_finalize(GObject *object)
{
    GwyToolReadValue *tool;
    GwyContainer *settings;

    tool = GWY_TOOL_READ_VALUE(object);

    g_free(tool->values);
    g_free(tool->xpos);
    g_free(tool->ypos);

    settings = gwy_app_settings_get();
    gwy_container_set_int32_by_name(settings, radius_key, tool->args.radius);
    gwy_container_set_boolean_by_name(settings, show_selection_key,
                                      tool->args.show_selection);

    if (tool->pixel_format)
        gwy_si_unit_value_format_free(tool->pixel_format);
    if (tool->angle_format)
        gwy_si_unit_value_format_free(tool->angle_format);

    G_OBJECT_CLASS(gwy_tool_read_value_parent_class)->finalize(object);
}
