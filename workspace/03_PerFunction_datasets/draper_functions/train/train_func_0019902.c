on_playlist_row_expanded (GtkTreeView *tree_view,
                          GtkTreeIter *iter,
                          GtkTreePath *path,
                          gpointer     user_data)
{
        GtkTreeModel *model;
        GtkTreeIter   child_iter;

        model = gtk_tree_view_get_model (GTK_TREE_VIEW (treeview));
        g_assert (model != NULL);

        if (!gtk_tree_model_iter_children (model, &child_iter, iter)) {
                return;
        }

        do {
                GUPnPServiceProxy *content_dir;
                gchar             *id;
                gboolean           is_container;
                gint              child_count;

                gtk_tree_model_get (model, &child_iter,
                                    3, &content_dir,
                                    4, &id,
                                    5, &is_container,
                                    6, &child_count,
                                    -1);

                if (is_container && child_count != 0) {
                        browse (content_dir, id, 0, MAX_BROWSE);
                }

                g_object_unref (content_dir);
                g_free (id);
        } while (gtk_tree_model_iter_next (model, &child_iter));
}
