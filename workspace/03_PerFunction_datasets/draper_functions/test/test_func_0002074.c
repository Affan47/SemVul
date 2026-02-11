dbus_connection_open_private (const char     *address,
                              DBusError      *error)
{
  DBusConnection *connection;

  _dbus_return_val_if_fail (address != NULL, NULL);
  _dbus_return_val_if_error_is_set (error, NULL);

  connection = _dbus_connection_open_internal (address,
                                               FALSE,
                                               error);

  return connection;
}
