FastaDB_expand_path_list(GPtrArray *path_list,
                                           gchar *suffix_filter){
    register GPtrArray *expanded_path_list = g_ptr_array_new();
    register gchar *path;
    register gint i;
    if(suffix_filter && (suffix_filter[0] == '.'))
        suffix_filter++;
    for(i = 0; i < path_list->len; i++){
        path = path_list->pdata[i];
        FastaDB_expand_path_list_recur(expanded_path_list,
                                       path, suffix_filter, FALSE);
        }
    if(!expanded_path_list->len){
        for(i = 0; i < path_list->len; i++)
            g_message("Empty path: [%s]", (gchar*)path_list->pdata[i]);
        g_error("No valid file paths found");
        }
    return expanded_path_list;
    }
