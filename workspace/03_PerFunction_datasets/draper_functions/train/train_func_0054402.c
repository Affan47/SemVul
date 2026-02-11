reload_thumbnail(FmFolderModel* model, GSequenceIter* seq_it, FmFolderItem* item)
{
    GtkTreeIter it;
    GtkTreePath* tp;
    if(item->is_thumbnail)
    {
        g_object_unref(item->icon);
        item->icon = NULL;
        it.stamp = model->stamp;
        it.user_data = seq_it;
        tp = fm_folder_model_get_path(GTK_TREE_MODEL(model), &it);
        gtk_tree_model_row_changed(GTK_TREE_MODEL(model), tp, &it);
        gtk_tree_path_free(tp);
    }
}
