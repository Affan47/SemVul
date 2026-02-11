dbus_connection_get_unix_fd (DBusConnection *connection,
                             int            *fd)
{
  _dbus_return_val_if_fail (connection != NULL, FALSE);
  _dbus_return_val_if_fail (connection->transport != NULL, FALSE);

#ifdef DBUS_WIN

  return FALSE;
#endif

  return dbus_connection_get_socket(connection, fd);
}
