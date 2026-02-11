dbus_connection_closed_cb (
    GDBusConnection *connection,
    gboolean remote_peer_vanished,
    GError *error,
    gpointer user_data)
{
  if (remote_peer_vanished)
    g_message ("remote peer disconnected: %s", error->message);
  else if (error != NULL)
    g_message ("remote peer sent broken data: %s", error->message);
  else
    g_message ("supposedly we closed the connection locally?!");

  g_object_unref (connection);
}
