space_set_ipod_itdb(iTunesDB *itdb) {
    const gchar *mp = NULL;

    if (itdb) {
        ExtraiTunesDBData *eitdb = itdb->userdata;
        g_return_if_fail (eitdb);

        if (!eitdb->ipod_ejected) {
            mp = itdb_get_mountpoint(itdb);
        }
    }

    _lock_mutex ();

    space_itdb = itdb;


    if (!space_mp || !mp || (strcmp(space_mp, mp) != 0)) {
        g_free(space_mp);
        space_mp = g_strdup(mp);

        space_data_update();
    }

    _unlock_mutex ();
}
