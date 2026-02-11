ario_playlist_get_drop_position (const int x,
                                 const int y)
{
        ARIO_LOG_FUNCTION_START;
        GtkTreeViewDropPosition pos;
        gint *indice;
        GtkTreePath *path = NULL;
        gint drop = 1;

        if (x < 0 || y < 0)
                return -1;


        gtk_tree_view_get_dest_row_at_pos (GTK_TREE_VIEW (instance->priv->tree), x, y, &path, &pos);

        if (!path)
                return -1;


        indice = gtk_tree_path_get_indices (path);
        drop = indice[0];

        if ((pos == GTK_TREE_VIEW_DROP_BEFORE
             || pos == GTK_TREE_VIEW_DROP_INTO_OR_BEFORE)
            && drop > 0)
                --drop;
        gtk_tree_path_free (path);

        return drop;
}
