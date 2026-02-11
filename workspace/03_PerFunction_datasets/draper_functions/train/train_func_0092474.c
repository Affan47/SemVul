connection_try_from_address_entry (DBusAddressEntry *entry,
                                   DBusError        *error)
{
  DBusTransport *transport;
  DBusConnection *connection;

  transport = _dbus_transport_open (entry, error);

  if (transport == NULL)
    {
      _DBUS_ASSERT_ERROR_IS_SET (error);
      return NULL;
    }

  connection = _dbus_connection_new_for_transport (transport);

  _dbus_transport_unref (transport);

  if (connection == NULL)
    {
      _DBUS_SET_OOM (error);
      return NULL;
    }

#ifndef DBUS_DISABLE_CHECKS
  _dbus_assert (!connection->have_connection_lock);
#endif
  return connection;
}
