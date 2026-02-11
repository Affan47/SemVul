explore_mark_new_dirs ( char * dir ) {
    GList * list;
    gchar * str;
    char buffer[BUFFER_SIZE];
    int len;

    strncpy(buffer, dir, BUFFER_SIZE);
    len = strlen(buffer);
    if (len && (buffer[len - 1] == '/'))
        buffer[len - 1] = '\0';

    if (strcmp(dir, gjay->prefs->song_root_dir) != 0) {
        if (explore_dir_has_new_songs(dir)) {
            str = g_strdup(dir);
            gjay->new_song_dirs = g_list_append(gjay->new_song_dirs, str);
            g_hash_table_insert(gjay->new_song_dirs_hash, str, str);
            explore_update_path_pm(dir, PM_DIR_CLOSED_NEW);
        }
    }

    for (list = explore_dirs_in_dir(buffer); list; list = g_list_next(list)) {
        explore_mark_new_dirs(list->data);
        g_free(list->data);
    }
    g_list_free(list);
}
