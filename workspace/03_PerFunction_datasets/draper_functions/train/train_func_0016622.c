_dbus_transport_new_for_socket (int               fd,
                                const DBusString *server_guid,
                                const DBusString *address)
{
  DBusTransportSocket *socket_transport;

  socket_transport = dbus_new0 (DBusTransportSocket, 1);
  if (socket_transport == NULL)
    return NULL;

  if (!_dbus_string_init (&socket_transport->encoded_outgoing))
    goto failed_0;

  if (!_dbus_string_init (&socket_transport->encoded_incoming))
    goto failed_1;

  socket_transport->write_watch = _dbus_watch_new (fd,
                                                 DBUS_WATCH_WRITABLE,
                                                 FALSE,
                                                 NULL, NULL, NULL);
  if (socket_transport->write_watch == NULL)
    goto failed_2;

  socket_transport->read_watch = _dbus_watch_new (fd,
                                                DBUS_WATCH_READABLE,
                                                FALSE,
                                                NULL, NULL, NULL);
  if (socket_transport->read_watch == NULL)
    goto failed_3;

  if (!_dbus_transport_init_base (&socket_transport->base,
                                  &socket_vtable,
                                  server_guid, address))
    goto failed_4;

#ifdef HAVE_UNIX_FD_PASSING
  _dbus_auth_set_unix_fd_possible(socket_transport->base.auth, _dbus_socket_can_pass_unix_fd(fd));
#endif

  socket_transport->fd = fd;
  socket_transport->message_bytes_written = 0;


  socket_transport->max_bytes_read_per_iteration = 2048;
  socket_transport->max_bytes_written_per_iteration = 2048;

  return (DBusTransport*) socket_transport;

 failed_4:
  _dbus_watch_invalidate (socket_transport->read_watch);
  _dbus_watch_unref (socket_transport->read_watch);
 failed_3:
  _dbus_watch_invalidate (socket_transport->write_watch);
  _dbus_watch_unref (socket_transport->write_watch);
 failed_2:
  _dbus_string_free (&socket_transport->encoded_incoming);
 failed_1:
  _dbus_string_free (&socket_transport->encoded_outgoing);
 failed_0:
  dbus_free (socket_transport);
  return NULL;
}
