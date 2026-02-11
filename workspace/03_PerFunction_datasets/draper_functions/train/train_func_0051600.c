gnc_item_list_num_entries (GncItemList *item_list)
{
    GtkTreeModel *model;

    g_return_val_if_fail(item_list != NULL, 0);
    g_return_val_if_fail(IS_GNC_ITEM_LIST(item_list), 0);

    model = GTK_TREE_MODEL(item_list->list_store);
    return gtk_tree_model_iter_n_children(model, NULL);
}
