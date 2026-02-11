gp_itdb_find_same_tracks_in_local_itdbs(Track *track) {
    GList *gl, *tracks = NULL;
    struct itdbs_head *ih = gp_get_itdbs_head();

    g_return_val_if_fail (ih, NULL);
    g_return_val_if_fail (track, NULL);

    for (gl = ih->itdbs; gl; gl = gl->next) {
        iTunesDB *itdb = gl->data;
        g_return_val_if_fail (itdb, tracks);
        if (itdb->usertype & GP_ITDB_TYPE_LOCAL) {
            GList *addtracks = gp_itdb_find_same_tracks(itdb, track);
            tracks = g_list_concat(tracks, addtracks);
        }
    }
    return tracks;
}
