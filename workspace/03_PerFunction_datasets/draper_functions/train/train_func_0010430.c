explore_view_set_root (const gchar* root_dir ) {
    GList * llist=NULL;
    char buffer[BUFFER_SIZE];

    if (!root_dir)
        return;

    gtk_tree_store_clear(store);
    gjay->tree_depth = 0;


    for (llist = g_list_first(gjay->songs); llist!=NULL; llist = g_list_next(llist)) {
        SONG(llist)->in_tree = FALSE;
    }


    if (files_to_add_queue) {
        while (!g_queue_is_empty(files_to_add_queue)) {
            g_free(files_to_add_queue->tail->data);
            g_queue_pop_tail(files_to_add_queue);
        }
    } else {
        files_to_add_queue  = g_queue_new();
    }

    for (llist = gjay->new_song_dirs; llist; llist = g_list_next(llist))
        g_free(llist->data);
    g_list_free(gjay->new_song_dirs);
    gjay->new_song_dirs = NULL;
    if (gjay->new_song_dirs_hash)
        g_hash_table_destroy(gjay->new_song_dirs_hash);
    gjay->new_song_dirs_hash = g_hash_table_new(g_str_hash, g_str_equal);

    if (name_iter_hash)
        g_hash_table_destroy(name_iter_hash);
    name_iter_hash = g_hash_table_new(g_str_hash, g_str_equal);

    for (llist = g_list_first(file_name_in_tree);
         llist;
         llist = g_list_next(llist)) {
        g_free(llist->data);
    }
    g_list_free(file_name_in_tree);
    file_name_in_tree = NULL;


    if (access(root_dir, R_OK | X_OK)) {
        snprintf(buffer, BUFFER_SIZE, "Cannot acces the base directory '%s'! Maybe it moved? You can pick another directory in the prefs", root_dir);
        g_warning(buffer);
        return;
    }
    if (iter_stack)
        g_queue_free (iter_stack);
    iter_stack = g_queue_new();

    if (parent_name_stack)
        g_queue_free(parent_name_stack);
    parent_name_stack = g_queue_new();

    if (files_to_analyze)
        g_list_free(files_to_analyze);
    files_to_analyze = NULL;


    gjay_ftw(root_dir, tree_walk, 10);

    gtk_idle_add(tree_add_idle, NULL);

    total_files_to_add = g_list_length(files_to_add_queue->head);
    file_to_add_count = 0;

    set_add_files_progress("Scanning tree...", 0);
    set_analysis_progress_visible(FALSE);
    set_add_files_progress_visible(TRUE);


    tree_add_idle(NULL);
}
