fm_folder_model_find_iter_by_filename(FmFolderModel* model, GtkTreeIter* it, const char* name)
{
    GSequenceIter *item_it = g_sequence_get_begin_iter(model->items);
    for( ; !g_sequence_iter_is_end(item_it); item_it = g_sequence_iter_next(item_it) )
    {
        FmFolderItem* item = (FmFolderItem*)g_sequence_get(item_it);
        FmPath* path = fm_file_info_get_path(item->inf);
        if( g_strcmp0(fm_path_get_basename(path), name) == 0 )
        {
            it->stamp = model->stamp;
            it->user_data  = item_it;
            return TRUE;
        }
    }
    return FALSE;
}
