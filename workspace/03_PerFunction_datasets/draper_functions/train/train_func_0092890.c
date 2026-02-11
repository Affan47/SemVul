dbus_connection_read_write_dispatch (DBusConnection *connection,
                                     int             timeout_milliseconds)
{
  _dbus_return_val_if_fail (connection != NULL, FALSE);
  _dbus_return_val_if_fail (timeout_milliseconds >= 0 || timeout_milliseconds == -1, FALSE);
   return _dbus_connection_read_write_dispatch(connection, timeout_milliseconds, TRUE);
}
