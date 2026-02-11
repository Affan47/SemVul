find_in_pending_thumbnail_requests(FmFolderModel* model, FmFileInfo* fi)
{
    GList* reqs = model->thumbnail_requests, *l;
    for(l=reqs;l;l=l->next)
    {
        FmThumbnailRequest* req = (FmThumbnailRequest*)l->data;
        FmFileInfo* fi2 = fm_thumbnail_request_get_file_info(req);
        FmPath* path = fm_file_info_get_path(fi);
        FmPath* path2 = fm_file_info_get_path(fi2);
        if(path && path2 && strcmp(fm_path_get_basename(path),
                                   fm_path_get_basename(path2)) == 0)
            return l;
    }
    return NULL;
}
