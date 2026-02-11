dbus_server_disconnect (DBusServer *server)
{
  _dbus_return_if_fail (server != NULL);

#ifdef DBUS_DISABLE_CHECKS
  _dbus_atomic_inc (&server->refcount);
#else
    {
      dbus_int32_t old_refcount = _dbus_atomic_inc (&server->refcount);

      _dbus_return_if_fail (old_refcount > 0);
    }
#endif

  SERVER_LOCK (server);

  _dbus_assert (server->vtable->disconnect != NULL);

  if (!server->disconnected)
    {

      server->disconnected = TRUE;

      (* server->vtable->disconnect) (server);
    }

  SERVER_UNLOCK (server);
  dbus_server_unref (server);
}
