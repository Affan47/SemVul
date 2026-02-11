on_thumbnail_max_changed(FmConfig* cfg, gpointer user_data)
{
    FmFolderModel* model = (FmFolderModel*)user_data;
    FmThumbnailRequest* req;
    GList* new_reqs = NULL;
    GSequenceIter* seq_it;
    FmFileInfo* fi;
    guint thumbnail_max_bytes = fm_config->thumbnail_max << 10;
    goffset size;

    seq_it = g_sequence_get_begin_iter(model->items);
    while( !g_sequence_iter_is_end(seq_it) )
    {
        FmFolderItem* item = (FmFolderItem*)g_sequence_get(seq_it);
        fi = item->inf;
        if(cfg->thumbnail_max)
        {


            if(thumbnail_max_bytes > model->thumbnail_max)
            {


                size = fm_file_info_get_size(fi);
                if(size < thumbnail_max_bytes && size > model->thumbnail_max )
                {


                    if(!item->thumbnail_failed && fm_file_info_can_thumbnail(fi)
                       && fm_file_info_is_image(fi))
                    {
                        req = fm_thumbnail_request(fi, model->icon_size, on_thumbnail_loaded, model);
                        new_reqs = g_list_append(new_reqs, req);
                    }
                }
            }
        }
        else
        {

            if(!item->is_thumbnail && !item->thumbnail_loading && !item->thumbnail_failed && fm_file_info_can_thumbnail(fi))
            {
                GList* l = find_in_pending_thumbnail_requests(model, fi);
                if(!l)
                {
                    req = fm_thumbnail_request(fi, model->icon_size, on_thumbnail_loaded, model);
                    new_reqs = g_list_append(new_reqs, req);
                }
            }
        }
        seq_it = g_sequence_iter_next(seq_it);
    }
    if(new_reqs)
        model->thumbnail_requests = g_list_concat(model->thumbnail_requests, new_reqs);
    model->thumbnail_max = thumbnail_max_bytes;
}
