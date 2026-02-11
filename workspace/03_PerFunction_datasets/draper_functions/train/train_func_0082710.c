read_data_into_auth (DBusTransport *transport,
                     dbus_bool_t   *oom)
{
  DBusTransportSocket *socket_transport = (DBusTransportSocket*) transport;
  DBusString *buffer;
  int bytes_read;

  *oom = FALSE;

  _dbus_auth_get_buffer (transport->auth, &buffer);

  bytes_read = _dbus_read_socket (socket_transport->fd,
                                  buffer, socket_transport->max_bytes_read_per_iteration);

  _dbus_auth_return_buffer (transport->auth, buffer,
                            bytes_read > 0 ? bytes_read : 0);

  if (bytes_read > 0)
    {
      _dbus_verbose (" read %d bytes in auth phase\n", bytes_read);

      return TRUE;
    }
  else if (bytes_read < 0)
    {


      if (_dbus_get_is_errno_enomem ())
        {
          *oom = TRUE;
        }
      else if (_dbus_get_is_errno_eagain_or_ewouldblock ())
        ;
      else
        {
          _dbus_verbose ("Error reading from remote app: %s\n",
                         _dbus_strerror_from_errno ());
          do_io_error (transport);
        }

      return FALSE;
    }
  else
    {
      _dbus_assert (bytes_read == 0);

      _dbus_verbose ("Disconnected from remote app\n");
      do_io_error (transport);

      return FALSE;
    }
}
