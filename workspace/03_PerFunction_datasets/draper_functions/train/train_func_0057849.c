get_itdb_filepath_hash(Playlist *pl) {
    GHashTable* filepath_hash;
    iTunesDB *itdb = pl->itdb;

    filepath_hash = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);

    GList *gl;
    for (gl = itdb->tracks; gl; gl = gl->next) {
        ExtraTrackData *etr;
        Track *track = gl->data;
        g_return_val_if_fail (track, NULL);

        etr = track->userdata;
        g_return_val_if_fail (etr, NULL);


        if (etr->pc_path_locale && *etr->pc_path_locale) {
            g_hash_table_insert(filepath_hash, g_strdup(etr->pc_path_locale), track);
        }
    }

    return filepath_hash;
}
