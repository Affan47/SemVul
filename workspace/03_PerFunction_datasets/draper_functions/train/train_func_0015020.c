each_rating_pl(iTunesDB *itdb) {
    gchar *str;
    guint playlist_nr;

    g_return_if_fail (itdb);
    str = _("Unrated tracks");
    for (playlist_nr = 0; playlist_nr < 6; playlist_nr++) {
        if (playlist_nr > 0) {
            str = g_strdup_printf(_("Rated %d"), playlist_nr);
        }
        update_ranked_playlist(itdb, str, 0, All_Ratings_IF, All_Ratings_CF, GUINT_TO_POINTER(playlist_nr));
    }
    g_free(str);
}
