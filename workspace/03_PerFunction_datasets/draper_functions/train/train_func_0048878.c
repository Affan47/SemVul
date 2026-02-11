seat_set_share_display_server (Seat *seat, gboolean share_display_server)
{
    g_return_if_fail (seat != NULL);
    seat->priv->share_display_server = share_display_server;
}
