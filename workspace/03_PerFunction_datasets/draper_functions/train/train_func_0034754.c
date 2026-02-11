_dbus_pending_call_new_unlocked (DBusConnection    *connection,
                                 int                timeout_milliseconds,
                                 DBusTimeoutHandler timeout_handler)
{
  DBusPendingCall *pending;
  DBusTimeout *timeout;

  _dbus_assert (timeout_milliseconds >= 0 || timeout_milliseconds == -1);

  if (timeout_milliseconds == -1)
    timeout_milliseconds = _DBUS_DEFAULT_TIMEOUT_VALUE;

  if (!dbus_pending_call_allocate_data_slot (&notify_user_data_slot))
    return NULL;

  pending = dbus_new0 (DBusPendingCall, 1);

  if (pending == NULL)
    {
      dbus_pending_call_free_data_slot (&notify_user_data_slot);
      return NULL;
    }

  if (timeout_milliseconds != DBUS_TIMEOUT_INFINITE)
    {
      timeout = _dbus_timeout_new (timeout_milliseconds,
                                   timeout_handler,
                                   pending, NULL);

      if (timeout == NULL)
        {
          dbus_pending_call_free_data_slot (&notify_user_data_slot);
          dbus_free (pending);
          return NULL;
        }

      pending->timeout = timeout;
    }
  else
    {
      pending->timeout = NULL;
    }

  _dbus_atomic_inc (&pending->refcount);
  pending->connection = connection;
  _dbus_connection_ref_unlocked (pending->connection);

  _dbus_data_slot_list_init (&pending->slot_list);

  _dbus_pending_call_trace_ref (pending, 0, 1, "new_unlocked");

  return pending;
}
