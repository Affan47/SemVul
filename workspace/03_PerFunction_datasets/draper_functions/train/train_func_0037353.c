fm_folder_model_col_get_name(FmFolderModelCol col_id)
{
    if(G_UNLIKELY((guint)col_id >= column_infos_n
       || column_infos[col_id] == NULL))
        return NULL;
    return column_infos[col_id]->name;
}
