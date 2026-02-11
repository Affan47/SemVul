gwy_tool_spot_remover_response(GwyTool *gwytool,
                               gint response_id)
{
    GwyToolSpotRemover *tool;

    GWY_TOOL_CLASS(gwy_tool_spot_remover_parent_class)->response(gwytool,
                                                                 response_id);

    tool = GWY_TOOL_SPOT_REMOVER(gwytool);
    if (response_id == GTK_RESPONSE_APPLY)
        gwy_tool_spot_remover_apply(tool);
    else if (response_id == GWY_TOOL_RESPONSE_CLEAR)
        gwy_selection_clear(tool->zselection);
}
