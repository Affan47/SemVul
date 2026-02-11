_dbus_transport_open_autolaunch (DBusAddressEntry  *entry,
                                 DBusTransport    **transport_p,
                                 DBusError         *error)
{
  const char *method;

  method = dbus_address_entry_get_method (entry);
  _dbus_assert (method != NULL);

  if (strcmp (method, "autolaunch") == 0)
    {
      const char *scope = dbus_address_entry_get_value (entry, "scope");

      *transport_p = _dbus_transport_new_for_autolaunch (scope, error);

      if (*transport_p == NULL)
        {
          _DBUS_ASSERT_ERROR_IS_SET (error);
          return DBUS_TRANSPORT_OPEN_DID_NOT_CONNECT;
        }
      else
        {
          _DBUS_ASSERT_ERROR_IS_CLEAR (error);
          return DBUS_TRANSPORT_OPEN_OK;
        }
    }
  else
    {
      _DBUS_ASSERT_ERROR_IS_CLEAR (error);
      return DBUS_TRANSPORT_OPEN_NOT_HANDLED;
    }
}
