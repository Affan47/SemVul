check_read_watch (DBusTransport *transport)
{
  DBusTransportSocket *socket_transport = (DBusTransportSocket*) transport;
  dbus_bool_t need_read_watch;

  _dbus_verbose ("fd = %d\n",socket_transport->fd);

  if (transport->connection == NULL)
    return;

  if (transport->disconnected)
    {
      _dbus_assert (socket_transport->read_watch == NULL);
      return;
    }

  _dbus_transport_ref (transport);

  if (_dbus_transport_get_is_authenticated (transport))
    need_read_watch =
      (_dbus_counter_get_size_value (transport->live_messages) < transport->max_live_messages_size) &&
      (_dbus_counter_get_unix_fd_value (transport->live_messages) < transport->max_live_messages_unix_fds);
  else
    {
      if (transport->receive_credentials_pending)
        need_read_watch = TRUE;
      else
        {


          DBusAuthState auth_state;

          auth_state = _dbus_auth_do_work (transport->auth);


          if (auth_state == DBUS_AUTH_STATE_WAITING_FOR_INPUT ||
              auth_state == DBUS_AUTH_STATE_WAITING_FOR_MEMORY ||
              auth_state == DBUS_AUTH_STATE_AUTHENTICATED)
            need_read_watch = TRUE;
          else
            need_read_watch = FALSE;
        }
    }

  _dbus_verbose ("  setting read watch enabled = %d\n", need_read_watch);
  _dbus_connection_toggle_watch_unlocked (transport->connection,
                                          socket_transport->read_watch,
                                          need_read_watch);

  _dbus_transport_unref (transport);
}
