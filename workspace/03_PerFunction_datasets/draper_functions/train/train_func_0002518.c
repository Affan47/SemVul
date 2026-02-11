fm_folder_reload(FmFolder* folder)
{
    GError* err = NULL;


    g_signal_emit(folder, signals[START_LOADING], 0);

    if(folder->dir_fi)
    {

        fm_file_info_unref(folder->dir_fi);
        folder->dir_fi = NULL;
    }


    GList* l = fm_file_info_list_peek_head_link(folder->files);


    if(folder->dirlist_job)
        free_dirlist_job(folder);


    if(l)
    {
        if(g_signal_has_handler_pending(folder, signals[FILES_REMOVED], 0, TRUE))
        {

            GSList* files_to_del = NULL;
            for(;l;l=l->next)
                files_to_del = g_slist_prepend(files_to_del, (FmFileInfo*)l->data);
            g_signal_emit(folder, signals[FILES_REMOVED], 0, files_to_del);
            g_slist_free(files_to_del);
        }
        fm_file_info_list_clear(folder->files);
    }


    if(folder->mon)
    {
        g_signal_handlers_disconnect_by_func(folder->mon, on_folder_changed, folder);
        g_object_unref(folder->mon);
    }
    folder->mon = fm_monitor_directory(folder->gf, &err);
    if(folder->mon)
    {
        g_signal_connect(folder->mon, "changed", G_CALLBACK(on_folder_changed), folder);
    }
    else
    {
        g_debug("file monitor cannot be created: %s", err->message);
        g_error_free(err);
        folder->mon = NULL;
    }

    g_signal_emit(folder, signals[CONTENT_CHANGED], 0);


    folder->defer_content_test = fm_config->defer_content_test;
    folder->dirlist_job = fm_dir_list_job_new2(folder->dir_path,
            folder->defer_content_test ? FM_DIR_LIST_JOB_FAST : FM_DIR_LIST_JOB_DETAILED);

    g_signal_connect(folder->dirlist_job, "finished", G_CALLBACK(on_dirlist_job_finished), folder);
    if(folder->wants_incremental)
        g_signal_connect(folder->dirlist_job, "files-found", G_CALLBACK(on_dirlist_job_files_found), folder);
    fm_dir_list_job_set_incremental(folder->dirlist_job, folder->wants_incremental);
    g_signal_connect(folder->dirlist_job, "error", G_CALLBACK(on_dirlist_job_error), folder);
    if (!fm_job_run_async(FM_JOB(folder->dirlist_job)))
    {
        folder->dirlist_job = NULL;
        g_object_unref(folder->dirlist_job);
        g_critical("failed to start directory listing job for the folder");
    }


    fm_folder_query_filesystem_info(folder);
}
