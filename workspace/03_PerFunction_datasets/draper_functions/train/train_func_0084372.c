on_file_info_job_finished(FmFileInfoJob* job, gpointer user_data)
{
    FmPlacesModel* model = FM_PLACES_MODEL(user_data);
    GList* l;
    GtkTreeIter it;
    FmPlacesItem* item;
    FmFileInfo* fi;
    FmPath* path;
    FmIcon* icon;
    GdkPixbuf* pix;


    model->jobs = g_slist_remove(model->jobs, job);
    g_signal_handlers_disconnect_by_func(job, on_file_info_job_finished, model);

    if(!gtk_tree_model_get_iter_first(GTK_TREE_MODEL(model), &it))
        goto finished;

    if(fm_file_info_list_is_empty(job->file_infos))
        goto finished;


    if(fm_file_info_list_get_length(job->file_infos) == 1)
    {
        fi = fm_file_info_list_peek_head(job->file_infos);
        do {
            item = NULL;
            gtk_tree_model_get(GTK_TREE_MODEL(model), &it, FM_PLACES_MODEL_COL_INFO, &item, -1);
            if( item && item->fi && (path = fm_file_info_get_path(item->fi)) && fm_path_equal(path, fm_file_info_get_path(fi)) )
            {
                fm_file_info_unref(item->fi);
                item->fi = fm_file_info_ref(fi);
                break;
            }
        }while(gtk_tree_model_iter_next(GTK_TREE_MODEL(model), &it));
    }
    else
    {
        do {
            item = NULL;
            gtk_tree_model_get(GTK_TREE_MODEL(model), &it, FM_PLACES_MODEL_COL_INFO, &item, -1);
            if( item && item->fi && (path = fm_file_info_get_path(item->fi)) )
            {
                for(l = fm_file_info_list_peek_head_link(job->file_infos); l; l = l->next )
                {
                    fi = FM_FILE_INFO(l->data);
                    if(fm_path_equal(path, fm_file_info_get_path(fi)))
                    {
                        fm_file_info_unref(item->fi);
                        item->fi = fm_file_info_ref(fi);

                        if(item->type == FM_PLACES_ITEM_PATH)
                        {
                            icon = fm_file_info_get_icon(fi);

                            if(icon && icon != item->icon)
                            {
                                g_object_unref(item->icon);
                                item->icon = g_object_ref(icon);
                                pix = fm_pixbuf_from_icon(icon, fm_config->pane_icon_size);
                                gtk_list_store_set(GTK_LIST_STORE(model), &it,
                                                   FM_PLACES_MODEL_COL_ICON, pix, -1);
                            }
                        }


                        fm_file_info_list_delete_link(job->file_infos, l);
                        break;
                    }
                }
            }
        }while(gtk_tree_model_iter_next(GTK_TREE_MODEL(model), &it));
    }
finished:
    g_object_unref(job);
}
