get_model_as_store(GtkTreeModel *model) {
    if (!GTK_IS_TREE_MODEL_FILTER (model))
        return GTK_LIST_STORE (model);
    else
        return GTK_LIST_STORE (gtk_tree_model_filter_get_model (GTK_TREE_MODEL_FILTER (model)));
}
