clarity_widget_playlist_removed_cb(GtkPodApp *app, gpointer pl, gpointer data) {
    g_return_if_fail(CLARITY_IS_WIDGET(data));

    ClarityWidget *cw = CLARITY_WIDGET(data);
    Playlist *playlist = (Playlist *) pl;
    if (!playlist)
        return;

    if (! gtk_widget_get_realized(GTK_WIDGET(cw)))
        return;

    if (cw->current_playlist == playlist)
        _clarity_widget_clear(cw);
}
