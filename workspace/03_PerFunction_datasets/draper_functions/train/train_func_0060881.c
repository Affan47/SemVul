gp_eject_ipod(iTunesDB *itdb) {

    g_return_val_if_fail (itdb, FALSE);
    g_return_val_if_fail (itdb->usertype & GP_ITDB_TYPE_IPOD, FALSE);

    if (gp_save_itdb(itdb)) {
        gint index;
        gchar *mountpoint;

        mountpoint = get_itdb_prefs_string(itdb, KEY_MOUNTPOINT);


        save_ipod_prefs(itdb, mountpoint);

        call_script("gtkpod.eject", mountpoint, FALSE);
        g_free(mountpoint);

        index = get_itdb_index(itdb);

        if (itdb->usertype & GP_ITDB_TYPE_AUTOMATIC) {
            remove_itdb_prefs(itdb);
            gp_itdb_remove(itdb);
            gp_itdb_free(itdb);
        }
        else {
            iTunesDB *new_itdb = setup_itdb_n(index);
            if (new_itdb) {
                ExtraiTunesDBData *new_eitdb;

                new_eitdb = new_itdb->userdata;
                g_return_val_if_fail (new_eitdb, TRUE);

                gp_replace_itdb(itdb, new_itdb);

                new_eitdb->ipod_ejected = TRUE;
            }
        }
        return TRUE;
    }
    return FALSE;
}
