update_dir_has_rating_color ( gchar * dir ) {
    gchar * parent;
    gchar * str;

    str = g_hash_table_lookup(gjay->new_song_dirs_hash, dir);
    if (!str)
        return;

    if (explore_dir_has_new_songs(dir))
        return;


    explore_update_path_pm(dir, PM_DIR_CLOSED);

    g_hash_table_remove(gjay->new_song_dirs_hash, str);
    gjay->new_song_dirs = g_list_remove(gjay->new_song_dirs, str);
    g_free(str);


    parent = parent_dir (dir);
    update_dir_has_rating_color(parent);
    g_free(parent);
}
