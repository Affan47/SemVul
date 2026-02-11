ario_filesystem_fill_filesystem (ArioFilesystem *filesystem)
{
        ARIO_LOG_FUNCTION_START;
        GtkTreeIter iter, fake_child;


        gtk_tree_store_clear (filesystem->priv->model);


        gtk_tree_store_append (filesystem->priv->model, &iter, NULL);
        gtk_tree_store_set (filesystem->priv->model, &iter,
                            FILETREE_ICON_COLUMN, GTK_STOCK_HARDDISK,
                            FILETREE_ICONSIZE_COLUMN, 1,
                            FILETREE_NAME_COLUMN, _("Music"),
                            FILETREE_DIR_COLUMN, ROOT, -1);


        gtk_tree_store_append(GTK_TREE_STORE (filesystem->priv->model), &fake_child, &iter);


        gtk_tree_selection_unselect_all (filesystem->priv->selection);
        if (gtk_tree_model_get_iter_first (GTK_TREE_MODEL (filesystem->priv->model), &iter)) {
                gtk_tree_selection_select_iter (filesystem->priv->selection, &iter);
                ario_filesystem_cursor_moved_cb (GTK_TREE_VIEW (filesystem->priv->tree), filesystem);
        }
        filesystem->priv->empty = FALSE;
}
