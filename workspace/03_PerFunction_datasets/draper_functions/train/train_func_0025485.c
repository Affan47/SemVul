key_store_key_removed (CryptUIKeyset *ckset, const gchar *key,
                       GtkTreeRowReference *ref, CryptUIKeyStore *ckstore)
{
    GtkTreeIter iter;
    GtkTreePath *path;

    g_return_if_fail (ref != NULL);

    path = gtk_tree_row_reference_get_path (ref);
    if (path) {
        if(gtk_tree_model_get_iter (GTK_TREE_MODEL (ckstore->priv->store), &iter, path))
            gtk_tree_store_remove (GTK_TREE_STORE (ckstore->priv->store), &iter);
        gtk_tree_path_free (path);
    }


    g_hash_table_remove (ckstore->priv->rows, key);
}
