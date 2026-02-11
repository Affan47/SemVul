on_row_loaded(FmDirTreeModel* fm_model, GtkTreePath* tp, FmDirTreeView* view)
{
    GtkTreeModel* model = GTK_TREE_MODEL(fm_model);
    GtkTreePath* ctp;

    g_return_if_fail(view->current_row);
    ctp = gtk_tree_row_reference_get_path(view->current_row);
    if(gtk_tree_path_compare(tp, ctp) != 0)
    {

        gtk_tree_path_free(ctp);
        return;
    }
    gtk_tree_path_free(ctp);


    g_signal_handlers_disconnect_by_func(model, on_row_loaded, view);


    gtk_tree_view_expand_row(GTK_TREE_VIEW(view), tp, FALSE);


    fm_path_unref(FM_PATH(view->paths_to_expand->data));
    view->paths_to_expand = g_slist_delete_link(view->paths_to_expand, view->paths_to_expand);

    if(view->paths_to_expand)
    {

        expand_pending_path(view, model, tp);
    }
    else
    {
        GtkTreeSelection* ts = gtk_tree_view_get_selection(GTK_TREE_VIEW(view));
        gtk_tree_selection_select_path(ts, tp);
        gtk_tree_view_scroll_to_cell(GTK_TREE_VIEW(view), tp, NULL, TRUE, 0.5, 0.5);
        gtk_tree_view_set_cursor(GTK_TREE_VIEW(view), tp, NULL, FALSE);
    }
}
