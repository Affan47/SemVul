explore_dir_has_new_songs ( char * dir ) {
    gboolean result = FALSE;
    GList * list;
    song * s;

    list = explore_files_in_dir(dir, TRUE);
    for (; list; list = g_list_next(list)) {
        if (result == FALSE) {
            s = g_hash_table_lookup(gjay->song_name_hash, list->data);
            if (s) {
                if (s->no_rating && s->no_color) {
                    result = TRUE;
                }
            } else if (verbosity) {
                fprintf(stderr, "Explore_dir_has_new_songs: missing dir %s\n",
                        dir);
            }
        }
        g_free(list->data);
    }
    g_list_free(list);
    return result;
}
