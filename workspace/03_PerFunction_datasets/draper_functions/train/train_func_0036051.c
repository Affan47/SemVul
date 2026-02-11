ario_audioscrobbler_song_changed_cb (ArioServer *server,
                                     ArioAudioscrobbler *audioscrobbler)
{
        ARIO_LOG_FUNCTION_START
        ArioServerSong *song;

        song = ario_server_get_current_song ();

        if (audioscrobbler->priv->currently_playing != NULL) {
                audioscrobbler_entry_free (audioscrobbler->priv->currently_playing);
                audioscrobbler->priv->currently_playing = NULL;
        }

        if (song == NULL) {
                ARIO_LOG_DBG ("called with no playing song");
                return;
        }

        audioscrobbler->priv->current_elapsed = ario_server_get_current_elapsed ();

        if (ario_audioscrobbler_is_queueable (song) && (audioscrobbler->priv->current_elapsed < 15)) {
                AudioscrobblerEntry *as_entry;


                as_entry = ario_audioscrobbler_create_entry (song);
                audioscrobbler->priv->currently_playing = as_entry;
        }
}
