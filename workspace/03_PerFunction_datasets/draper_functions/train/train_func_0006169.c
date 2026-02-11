update_group_states(GtkTreeModel *model)
{
    GroupState group_states[GWY_GRAIN_VALUE_GROUP_USER+1];
    GrainValueStorePrivate *priv;
    GtkTreeIter iter;

    gwy_clear(group_states, GWY_GRAIN_VALUE_GROUP_USER+1);

    gtk_tree_model_foreach(model, update_state, group_states);
    if (!gtk_tree_model_get_iter_first(model, &iter))
        return;

    priv = g_object_get_qdata(G_OBJECT(model), priv_quark);
    do {
        GwyGrainValueGroup group;
        GtkTreePath *path;

        gtk_tree_model_get(model, &iter,
                           GWY_GRAIN_VALUE_STORE_COLUMN_GROUP, &group,
                           -1);
        if (group_states[group] != priv->group_states[group]) {
            priv->group_states[group] = group_states[group];
            path = gtk_tree_model_get_path(model, &iter);
            gtk_tree_model_row_changed(model, path, &iter);
            gtk_tree_path_free(path);
        }
    } while (gtk_tree_model_iter_next(model, &iter));
}
