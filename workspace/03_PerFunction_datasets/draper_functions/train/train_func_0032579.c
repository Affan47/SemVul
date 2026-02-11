fm_dir_tree_row_get_file_info(FmDirTreeModel* model, GtkTreeIter* iter)
{
    GList* item_l;
    FmDirTreeItem *item;

    g_return_val_if_fail (iter->stamp == model->stamp, NULL);

    item_l = (GList*)iter->user_data;
    item = (FmDirTreeItem*)item_l->data;

    return item->fi;
}
