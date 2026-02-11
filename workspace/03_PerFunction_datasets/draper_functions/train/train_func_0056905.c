add_bookmarks(FmPlacesModel* model, FmFileInfoJob* job)
{
    FmPlacesItem* item;
    GList *bms, *l;
    FmIcon* icon = fm_icon_from_name("folder");
    FmIcon* remote_icon = NULL;
    GdkPixbuf* folder_pix = fm_pixbuf_from_icon(icon, fm_config->pane_icon_size);
    GdkPixbuf* remote_pix = NULL;
    bms = fm_bookmarks_get_all(model->bookmarks);
    for(l=bms;l;l=l->next)
    {
        FmBookmarkItem* bm = (FmBookmarkItem*)l->data;
        GtkTreeIter it;
        GdkPixbuf* pix;
        FmPath* path = bm->path;

        item = add_new_item(GTK_LIST_STORE(model), FM_PLACES_ITEM_PATH, &it, NULL);
        fm_file_info_set_path(item->fi, path);
        fm_file_info_job_add(job, path);
        if(fm_path_is_native(path))
        {
            item->icon = g_object_ref(icon);
            pix = folder_pix;
        }
        else
        {
            if(G_UNLIKELY(!remote_icon))
            {
                remote_icon = fm_icon_from_name("folder-remote");
                remote_pix = fm_pixbuf_from_icon(remote_icon, fm_config->pane_icon_size);
            }
            item->icon = g_object_ref(remote_icon);
            pix = remote_pix;
        }
        item->bm_item = bm;
        item->id = FM_PLACES_ID_OTHER;
        gtk_list_store_set(GTK_LIST_STORE(model), &it,
                           FM_PLACES_MODEL_COL_ICON, pix,
                           FM_PLACES_MODEL_COL_LABEL, bm->name, -1);
    }
    g_list_free(bms);
    g_object_unref(folder_pix);
    g_object_unref(icon);
    if(remote_icon)
    {
        g_object_unref(remote_icon);
        if(remote_pix)
            g_object_unref(remote_pix);
    }
}
