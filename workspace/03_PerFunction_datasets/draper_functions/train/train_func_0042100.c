gnc_plugin_page_sx_list_cmd_delete(GtkAction *action, GncPluginPageSxList *page)
{
    GncPluginPageSxListPrivate *priv = GNC_PLUGIN_PAGE_SX_LIST_GET_PRIVATE(page);
    GtkTreeSelection *selection;
    GList *selected_paths, *to_delete = NULL;
    GtkTreeModel *model;

    selection = gtk_tree_view_get_selection(priv->tree_view);
    selected_paths = gtk_tree_selection_get_selected_rows(selection, &model);
    if (g_list_length(selected_paths) == 0)
    {
        g_warning("no selection for delete.");
        return;
    }

    to_delete = gnc_g_list_map(selected_paths,
                               (GncGMapFunc)_argument_reorder_fn,
                               priv->tree_view);
    {
        GList *list;
        for (list = to_delete; list != NULL; list = list->next)
        {
            g_debug("to-delete [%s]\n", xaccSchedXactionGetName((SchedXaction*)list->data));
        }
    }


    if (gnc_verify_dialog(NULL, FALSE, "%s", _("Do you really want to delete this scheduled transaction?")))
    {
        g_list_foreach(to_delete, (GFunc)_destroy_sx, NULL);
    }

    g_list_free(to_delete);
    g_list_foreach(selected_paths, (GFunc)gtk_tree_path_free, NULL);
    g_list_free(selected_paths);
}
