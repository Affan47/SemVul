dbus_connection_get_g_connection (DBusConnection *connection)
{
  g_return_val_if_fail (connection, NULL);
  g_return_val_if_fail (dbus_connection_get_data (connection, _dbus_gmain_connection_slot), NULL);

  return DBUS_G_CONNECTION_FROM_CONNECTION (connection);
}
