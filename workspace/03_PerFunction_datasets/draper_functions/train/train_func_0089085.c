dbus_g_bus_get_private (DBusBusType     type,
                        GMainContext   *context,
                        GError        **error)
{
  DBusConnection *connection;
  DBusError derror;

  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  _dbus_g_value_types_init ();

  dbus_error_init (&derror);

  connection = dbus_bus_get_private (type, &derror);
  if (connection == NULL)
    {
      dbus_set_g_error (error, &derror);
      dbus_error_free (&derror);
      return NULL;
    }


  dbus_connection_setup_with_g_main (connection, context);

  return DBUS_G_CONNECTION_FROM_CONNECTION (connection);
}
