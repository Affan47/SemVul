get_selected_object (MetadataFunc callback,
                     gpointer     user_data)
{
        GUPnPServiceProxy  *content_dir;
        GtkTreeSelection   *selection;
        GtkTreeModel       *model;
        GtkTreeIter         iter;
        char               *id = NULL;
        gboolean            ret = FALSE;

        selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (treeview));
        g_assert (selection != NULL);

        if (!gtk_tree_selection_get_selected (selection, &model, &iter)) {
                goto return_point;
        }

        gtk_tree_model_get (model,
                            &iter,
                            3, &content_dir,
                            4, &id,
                            -1);

        browse_metadata (g_object_ref (content_dir), id, callback, user_data);

        ret = TRUE;

        if (id) {
                g_free (id);
        }

        g_object_unref (content_dir);

return_point:
        return ret;
}
