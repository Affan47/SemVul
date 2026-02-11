key_store_row_add (CryptUIKeyStore *ckstore, const gchar *key, GtkTreeIter *iter)
{
    GtkTreePath *path;
    GtkTreeRowReference *ref;


    ref = (GtkTreeRowReference*)g_hash_table_lookup (ckstore->priv->rows, key);
    if (ref != NULL) {


        path = gtk_tree_row_reference_get_path (ref);
        if (path != NULL) {
            gtk_tree_model_get_iter (GTK_TREE_MODEL (ckstore->priv->store), iter, path);
            return;
        }
    }

    gtk_tree_store_append (GTK_TREE_STORE (ckstore->priv->store), iter, NULL);
    path = gtk_tree_model_get_path (GTK_TREE_MODEL (ckstore->priv->store), iter);
    ref = gtk_tree_row_reference_new (GTK_TREE_MODEL (ckstore->priv->store), path);
    gtk_tree_path_free (path);

    g_hash_table_replace (ckstore->priv->rows, (gchar*)key, ref);
    gtk_tree_store_set (GTK_TREE_STORE (ckstore->priv->store), iter, CRYPTUI_KEY_STORE_KEY, key, -1);
}
