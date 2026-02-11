add_tracks_to_playlist(Playlist *pl, gchar *string, GList *tracks) {

    g_return_if_fail (!(string && tracks));
    g_return_if_fail (pl);
    g_return_if_fail (pl->itdb);
    g_return_if_fail (itdb_playlist_mpl (pl->itdb));
    if (!(string || tracks))
        return;

    if (string) {
        Track *track;
        gchar *str = string;
        while (parse_tracks_from_string(&str, &track)) {
            g_return_if_fail (track);
            intern_add_track(pl, track);
        }
    }
    if (tracks) {
        GList *gl;
        for (gl = tracks; gl; gl = gl->next) {
            Track *track = gl->data;
            g_return_if_fail (track);
            intern_add_track(pl, track);
        }
    }
}
