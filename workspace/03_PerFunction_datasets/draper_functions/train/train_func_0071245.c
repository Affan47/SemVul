gwy_data_chooser_is_visible(GtkTreeModel *model,
                            GtkTreeIter *iter,
                            gpointer data)
{
    GwyDataChooser *chooser = (GwyDataChooser*)data;
    GwyContainer *container;
    guint id;

    gtk_tree_model_get(model, iter,
                       MODEL_COLUMN_CONTAINER, &container,
                       MODEL_COLUMN_ID, &id,
                       -1);


    if (!container)
        return chooser->none_label != NULL;

    g_object_unref(container);
    if (!chooser->filter_func)
        return TRUE;

    return chooser->filter_func(container, id, chooser->filter_data);
}
