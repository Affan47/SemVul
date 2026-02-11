_dbus_transport_do_iteration (DBusTransport  *transport,
                              unsigned int    flags,
                              int             timeout_milliseconds)
{
  _dbus_assert (transport->vtable->do_iteration != NULL);

  _dbus_verbose ("Transport iteration flags 0x%x timeout %d connected = %d\n",
                 flags, timeout_milliseconds, !transport->disconnected);

  if ((flags & (DBUS_ITERATION_DO_WRITING |
                DBUS_ITERATION_DO_READING)) == 0)
    return;

  if (transport->disconnected)
    return;

  _dbus_transport_ref (transport);
  (* transport->vtable->do_iteration) (transport, flags,
                                       timeout_milliseconds);
  _dbus_transport_unref (transport);

  _dbus_verbose ("end\n");
}
