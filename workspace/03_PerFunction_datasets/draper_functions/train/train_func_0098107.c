sync_playlist_mode_none_toggled(GtkToggleButton *togglebutton) {
    gchar *key;

    g_return_if_fail (repository_view);

    key = get_playlist_prefs_key(repository_view->itdb_index, repository_view->playlist, KEY_SYNCMODE);

    if (gtk_toggle_button_get_active(togglebutton)) {
        finish_int_storage(key, SYNC_PLAYLIST_MODE_NONE);
        gtk_widget_set_sensitive(GET_WIDGET (repository_view->builder, MANUAL_SYNCDIR_CHOOSER), FALSE);
        update_buttons();
    }

    g_free(key);
}
