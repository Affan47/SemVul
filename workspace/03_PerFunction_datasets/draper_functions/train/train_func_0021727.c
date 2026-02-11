fm_dir_tree_model_iter_n_children(GtkTreeModel *tree_model,
                                              GtkTreeIter *iter)
{
    FmDirTreeModel* model;
    GList* children;
    g_return_val_if_fail(FM_IS_DIR_TREE_MODEL(tree_model), -1);

    model = (FmDirTreeModel*)tree_model;

    if(!iter)
        children = model->roots;
    else
    {
        GList* item_l = (GList*)iter->user_data;
        FmDirTreeItem* item = (FmDirTreeItem*)item_l->data;
        children = item->children;
    }
    return g_list_length(children);
}
