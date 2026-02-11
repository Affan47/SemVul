display_server_transition_plymouth_cb (DisplayServer *display_server, Seat *seat)
{

    if (plymouth_get_is_running ())
        plymouth_quit (FALSE);

    g_signal_handlers_disconnect_matched (display_server, G_SIGNAL_MATCH_FUNC, 0, 0, NULL, display_server_transition_plymouth_cb, NULL);
}
