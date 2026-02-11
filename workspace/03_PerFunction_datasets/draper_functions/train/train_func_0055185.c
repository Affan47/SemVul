gwy_tool_distance_finalize(GObject *object)
{
    GwyToolDistance *tool;

    tool = GWY_TOOL_DISTANCE(object);

    if (tool->model) {
        gtk_tree_view_set_model(tool->treeview, NULL);
        gwy_object_unref(tool->model);
    }
    if (tool->angle_format)
        gwy_si_unit_value_format_free(tool->angle_format);

    G_OBJECT_CLASS(gwy_tool_distance_parent_class)->finalize(object);
}
