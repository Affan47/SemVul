gwy_tool_roughness_response(GwyTool *tool,
                            gint response_id)
{
    GWY_TOOL_CLASS(gwy_tool_roughness_parent_class)->response(tool,
                                                              response_id);

    if (response_id == GTK_RESPONSE_APPLY)
        gwy_tool_roughness_apply(GWY_TOOL_ROUGHNESS(tool));
}
