gnc_tree_model_owner_get_iter (GtkTreeModel *tree_model,
                               GtkTreeIter *iter,
                               GtkTreePath *path)
{
    GncTreeModelOwnerPrivate *priv;
    GncTreeModelOwner *model;
    GncOwner *owner;
    gint *indices;

    g_return_val_if_fail (GNC_IS_TREE_MODEL_OWNER (tree_model), FALSE);

    {
        gchar *path_string = gtk_tree_path_to_string(path);
        ENTER("model %p, iter %p, path %s", tree_model, iter, path_string);
        g_free(path_string);
    }

    model = GNC_TREE_MODEL_OWNER (tree_model);
    priv = GNC_TREE_MODEL_OWNER_GET_PRIVATE(model);


    if (gtk_tree_path_get_depth (path) != 1)
    {
        LEAVE("bad depth");
        return FALSE;
    }

    indices = gtk_tree_path_get_indices (path);

    owner = g_list_nth_data (priv->owner_list, indices[0]);
    if (owner == NULL)
    {
        iter->stamp = 0;
        LEAVE("bad index");
        return FALSE;
    }

    iter->stamp = model->stamp;
    iter->user_data = owner;
    iter->user_data2 = GINT_TO_POINTER (indices[0]);
    iter->user_data3 = NULL;

    LEAVE("iter %s", iter_to_string (iter));
    return TRUE;
}
