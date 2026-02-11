Browser_List_Row_Selected (GtkTreeSelection *selection, gpointer data)
{
    GList *selectedRows;
    GtkTreePath *lastSelected;
    GtkTreeIter lastFile;
    ET_File *fileETFile;

    selectedRows = gtk_tree_selection_get_selected_rows(selection, NULL);


    if (!selectedRows)
    {
        return;
    }

    if (!LastBrowserListETFileSelected)
    {

        lastSelected = (GtkTreePath *)g_list_last(selectedRows)->data;
        if (gtk_tree_model_get_iter(GTK_TREE_MODEL(fileListModel), &lastFile, lastSelected))
            gtk_tree_model_get(GTK_TREE_MODEL(fileListModel), &lastFile,
                               LIST_FILE_POINTER, &fileETFile, -1);

        Action_Select_Nth_File_By_Etfile(fileETFile);
    }else
    {

        Action_Select_Nth_File_By_Etfile(LastBrowserListETFileSelected);
    }

    g_list_free_full (selectedRows, (GDestroyNotify)gtk_tree_path_free);
}
