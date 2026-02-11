_dbus_transport_init_base (DBusTransport             *transport,
                           const DBusTransportVTable *vtable,
                           const DBusString          *server_guid,
                           const DBusString          *address)
{
  DBusMessageLoader *loader;
  DBusAuth *auth;
  DBusCounter *counter;
  char *address_copy;
  DBusCredentials *creds;

  loader = _dbus_message_loader_new ();
  if (loader == NULL)
    return FALSE;

  if (server_guid)
    auth = _dbus_auth_server_new (server_guid);
  else
    auth = _dbus_auth_client_new ();
  if (auth == NULL)
    {
      _dbus_message_loader_unref (loader);
      return FALSE;
    }

  counter = _dbus_counter_new ();
  if (counter == NULL)
    {
      _dbus_auth_unref (auth);
      _dbus_message_loader_unref (loader);
      return FALSE;
    }

  creds = _dbus_credentials_new ();
  if (creds == NULL)
    {
      _dbus_counter_unref (counter);
      _dbus_auth_unref (auth);
      _dbus_message_loader_unref (loader);
      return FALSE;
    }

  if (server_guid)
    {
      _dbus_assert (address == NULL);
      address_copy = NULL;
    }
  else
    {
      _dbus_assert (address != NULL);

      if (!_dbus_string_copy_data (address, &address_copy))
        {
          _dbus_credentials_unref (creds);
          _dbus_counter_unref (counter);
          _dbus_auth_unref (auth);
          _dbus_message_loader_unref (loader);
          return FALSE;
        }
    }

  transport->refcount = 1;
  transport->vtable = vtable;
  transport->loader = loader;
  transport->auth = auth;
  transport->live_messages = counter;
  transport->authenticated = FALSE;
  transport->disconnected = FALSE;
  transport->is_server = (server_guid != NULL);
  transport->send_credentials_pending = !transport->is_server;
  transport->receive_credentials_pending = transport->is_server;
  transport->address = address_copy;

  transport->unix_user_function = NULL;
  transport->unix_user_data = NULL;
  transport->free_unix_user_data = NULL;

  transport->windows_user_function = NULL;
  transport->windows_user_data = NULL;
  transport->free_windows_user_data = NULL;

  transport->expected_guid = NULL;


  transport->max_live_messages_size = _DBUS_ONE_MEGABYTE * 63;


  transport->max_live_messages_unix_fds = 4096;


  transport->credentials = creds;

  _dbus_counter_set_notify (transport->live_messages,
                            transport->max_live_messages_size,
                            transport->max_live_messages_unix_fds,
                            live_messages_notify,
                            transport);

  if (transport->address)
    _dbus_verbose ("Initialized transport on address %s\n", transport->address);

  return TRUE;
}
