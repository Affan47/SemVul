gwy_tool_profile_selection_changed(GwyPlainTool *plain_tool,
                                   gint hint)
{
    GwyToolProfile *tool;
    GwyNullStore *store;
    gint n;

    tool = GWY_TOOL_PROFILE(plain_tool);
    store = GWY_NULL_STORE(tool->model);
    n = gwy_null_store_get_n_rows(store);
    g_return_if_fail(hint <= n);

    if (hint < 0) {
        gtk_tree_view_set_model(tool->treeview, NULL);
        if (plain_tool->selection)
            n = gwy_selection_get_data(plain_tool->selection, NULL);
        else
            n = 0;
        gwy_null_store_set_n_rows(store, n);
        gtk_tree_view_set_model(tool->treeview, tool->model);
        gwy_graph_model_remove_all_curves(tool->gmodel);
        gwy_tool_profile_update_all_curves(tool);
    }
    else {
        if (hint < n)
            gwy_null_store_row_changed(store, hint);
        else
            gwy_null_store_set_n_rows(store, n+1);
        gwy_tool_profile_update_curve(tool, hint);
        n++;
    }

    gtk_widget_set_sensitive(tool->apply, n > 0);
}
