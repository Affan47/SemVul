save_ipod_prefs(iTunesDB *itdb, const gchar *mountpoint) {
    g_return_val_if_fail (itdb && mountpoint, FALSE);
    return save_ipod_index_prefs(get_itdb_index(itdb), mountpoint);
}
