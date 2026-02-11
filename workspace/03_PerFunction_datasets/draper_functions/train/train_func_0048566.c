fm_folder_model_add_custom_column(const char* name,
                                                   FmFolderModelColumnInit* init)
{
    FmFolderModelInfo* info;
    guint i;

    g_return_val_if_fail(name && init && init->title && init->get_type &&
                         init->get_value, FM_FOLDER_MODEL_COL_DEFAULT);
    for(i = 0; i < column_infos_n; i++)
        if(strcmp(name, column_infos[i]->name) == 0)
            return FM_FOLDER_MODEL_COL_DEFAULT;
    column_infos = g_realloc(column_infos, sizeof(FmFolderModelInfo*) * (i+1));
    info = g_new0(FmFolderModelInfo, 1);
    column_infos[i] = info;
    column_infos_n = i+1;
    info->type = init->get_type();
    info->name = g_strdup(name);
    info->title = g_strdup(init->title);
    info->sortable = (init->compare != NULL);
    info->default_width = init->default_width;
    info->get_value = init->get_value;
    info->compare = init->compare;
    return i;
}
