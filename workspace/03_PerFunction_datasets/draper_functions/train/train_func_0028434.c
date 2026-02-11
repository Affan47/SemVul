dbus_connection_set_route_peer_messages (DBusConnection             *connection,
                                         dbus_bool_t                 value)
{
  _dbus_return_if_fail (connection != NULL);

  CONNECTION_LOCK (connection);
  connection->route_peer_messages = value;
  CONNECTION_UNLOCK (connection);
}
