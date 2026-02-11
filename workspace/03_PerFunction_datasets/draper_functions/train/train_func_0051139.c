on_item_selected (GtkTreeSelection *selection,
                  gpointer          user_data)
{
        PlaybackState state;

        state = get_selected_renderer_state ();

        if (state == PLAYBACK_STATE_PLAYING ||
            state == PLAYBACK_STATE_PAUSED) {
                if (!get_selected_object ((MetadataFunc) set_av_transport_uri,
                                          NULL)) {
                        av_transport_send_action ("Stop", NULL);
                }
       }
}
