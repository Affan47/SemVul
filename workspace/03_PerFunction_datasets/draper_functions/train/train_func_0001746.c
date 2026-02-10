fm_dir_tree_view_dispose(GObject *object)
{
    FmDirTreeView *view;

    g_return_if_fail(object != NULL);
    g_return_if_fail(FM_IS_DIR_TREE_VIEW(object));

    view = (FmDirTreeView*)object;
    if(G_UNLIKELY(view->paths_to_expand))
    {
        GtkTreeModel* model = gtk_tree_view_get_model(GTK_TREE_VIEW(view));
        cancel_pending_chdir(model, view);
    }
    if(view->current_row)
    {
        gtk_tree_row_reference_free(view->current_row);
        view->current_row = NULL;
    }
    if(view->cwd)
    {
        fm_path_unref(view->cwd);
        view->cwd = NULL;
    }
    if(view->dd)
    {
        g_object_unref(view->dd);
        view->dd = NULL;
    }

    G_OBJECT_CLASS(fm_dir_tree_view_parent_class)->dispose(object);
}
