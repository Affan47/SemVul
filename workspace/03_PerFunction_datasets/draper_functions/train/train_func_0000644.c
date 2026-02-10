Mask_Editor_List_Move_Down (void)
{
    GtkTreeSelection *selection;
    GList *selectedRows;
    GList *l;
    GtkTreeIter currentFile;
    GtkTreeIter nextFile;
    GtkTreePath *currentPath;
    GtkTreeModel *treemodel;

    g_return_if_fail (MaskEditorList != NULL);

    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(MaskEditorList));
    treemodel = gtk_tree_view_get_model(GTK_TREE_VIEW(MaskEditorList));
    selectedRows = gtk_tree_selection_get_selected_rows(selection, NULL);

    if (!selectedRows)
    {
        Log_Print(LOG_ERROR,_("Move Down: No row selected"));
        return;
    }

    for (l = selectedRows; l != NULL; l = g_list_next (l))
    {
        currentPath = (GtkTreePath *)l->data;

        if (gtk_tree_model_get_iter(treemodel, &currentFile, currentPath))
        {

            gtk_tree_path_next(currentPath);
            if (gtk_tree_model_get_iter(treemodel, &nextFile, currentPath))
                gtk_list_store_swap(GTK_LIST_STORE(treemodel), &currentFile, &nextFile);
        }
    }

    g_list_free_full (selectedRows, (GDestroyNotify)gtk_tree_path_free);
}
