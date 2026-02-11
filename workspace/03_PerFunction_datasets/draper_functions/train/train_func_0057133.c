gwy_resource_editor_get_active(GwyResourceEditor *editor,
                               GtkTreeModel **model,
                               GtkTreeIter *iter,
                               const gchar *warnwhat)
{
    GtkTreeSelection *selection;
    GwyResource *resource;
    GtkTreeModel *treemodel;
    GtkTreeIter treeiter;

    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(editor->treeview));
    if (!gtk_tree_selection_get_selected(selection, &treemodel, &treeiter)) {
        if (warnwhat)
            g_critical("Something must be selected for `%s'!", warnwhat);
        *model = NULL;
        return NULL;
    }

    gtk_tree_model_get(treemodel, &treeiter, 0, &resource, -1);
    if (model)
        *model = treemodel;
    if (iter)
        *iter = treeiter;

    return resource;
}
