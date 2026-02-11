gwy_tool_selection_manager_response(GwyTool *gwytool,
                                    gint response_id)
{
    GwyToolSelectionManager *tool;

    GWY_TOOL_CLASS(gwy_tool_selection_manager_parent_class)->response(gwytool,
                                                                      response_id);

    tool = GWY_TOOL_SELECTION_MANAGER(gwytool);
    if (response_id == GWY_TOOL_RESPONSE_CLEAR)
        gwy_tool_selection_manager_clear(tool);
}
