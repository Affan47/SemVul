gwy_tool_line_stats_apply(GwyToolLineStats *tool)
{
    GwyPlainTool *plain_tool;
    GwyGraphModel *gmodel;

    plain_tool = GWY_PLAIN_TOOL(tool);
    g_return_if_fail(plain_tool->selection);

    gmodel = gwy_graph_model_duplicate(tool->gmodel);
    gwy_app_data_browser_add_graph_model(gmodel, plain_tool->container, TRUE);
    g_object_unref(gmodel);
}
