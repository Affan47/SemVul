update_cb (void * hook_data, void * user_data)
{
    g_return_if_fail (playing);

    if (GPOINTER_TO_INT (hook_data) < PLAYLIST_UPDATE_METADATA || ! drct_get_ready ())
        return;

    if (update_from_playlist ())
        event_queue ("title change", NULL);
}
