run_as_playlist(guint playlist_minutes, gboolean m3u_format, gboolean player_autostart)
{
    GList * list;
    gjay->prefs->use_selected_songs = FALSE;
    gjay->prefs->rating_cutoff = FALSE;
    for (list = g_list_first(gjay->songs); list;  list = g_list_next(list)) {
        SONG(list)->in_tree = TRUE;
    }
    if (playlist_minutes == 0)
      playlist_minutes = gjay->prefs->time;
    list = generate_playlist(playlist_minutes);
    if (player_autostart) {
        play_songs(list);
    } else {
        write_playlist(list, stdout, m3u_format);
    }
    g_list_free(list);
}
