bacon_message_connection_send (BaconMessageConnection *conn,
                   const char *message)
{
    g_return_if_fail (conn != NULL);
    g_return_if_fail (message != NULL);

    g_io_channel_write_chars (conn->chan, message, strlen (message),
                  NULL, NULL);
    g_io_channel_write_chars (conn->chan, "\n", 1, NULL, NULL);
    g_io_channel_flush (conn->chan, NULL);
}
