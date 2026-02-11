CompoundFile_create(GPtrArray *path_list,
                                  gboolean sort_on_file_size){
    register CompoundFile *cf = g_new(CompoundFile, 1);
    register CompoundFile_Element *cfe;
    register CompoundFile_Pos length;
    register gint i;
    register gchar *path;
    g_assert(path_list);
    g_assert(path_list->len);
    cf->ref_count = 1;
    cf->element_list = g_ptr_array_new();
    cf->fp = NULL;
    cf->curr_element_id = -1;

    for(i = 0; i < path_list->len; i++){
        path = path_list->pdata[i];

        length = CompoundFile_size_from_path(path);
        cfe = CompoundFile_Element_create(path, length);
        g_ptr_array_add(cf->element_list, cfe);
        }
    cf->start_limit = cf->stop_limit = NULL;
    if(sort_on_file_size)
        CompoundFile_sort(cf);
    CompoundFile_rewind(cf);
#ifdef USE_PTHREADS
    pthread_mutex_init(&cf->compoundfile_mutex, NULL);
#endif
    return cf;
    }
