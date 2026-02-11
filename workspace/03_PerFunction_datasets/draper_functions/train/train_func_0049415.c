fm_path_list_new_from_file_info_list(FmFileInfoList* fis)
{
    FmPathList* list = fm_path_list_new();
    GList* l;
    for(l=fm_list_peek_head_link((FmList*)fis);l;l=l->next)
    {
        FmFileInfo* fi = (FmFileInfo*)l->data;
        fm_path_list_push_tail(list, fm_file_info_get_path(fi));
    }
    return list;
}
