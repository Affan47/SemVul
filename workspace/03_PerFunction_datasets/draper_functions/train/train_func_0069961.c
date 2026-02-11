gwy_tool_sfunctions_instant_update_changed(GtkToggleButton *check,
                                           GwyToolSFunctions *tool)
{
    tool->args.instant_update = gtk_toggle_button_get_active(check);
    gwy_tool_sfunctions_update_sensitivity(tool);
    if (tool->args.instant_update)
        gwy_tool_sfunctions_update_curve(tool);
}
