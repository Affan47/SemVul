free_pending_call_on_hash_removal (void *data)
{
  DBusPendingCall *pending;
  DBusConnection  *connection;

  if (data == NULL)
    return;

  pending = data;

  connection = _dbus_pending_call_get_connection_unlocked (pending);

  HAVE_LOCK_CHECK (connection);

  if (_dbus_pending_call_is_timeout_added_unlocked (pending))
    {
      _dbus_connection_remove_timeout_unlocked (connection,
                                                _dbus_pending_call_get_timeout_unlocked (pending));

      _dbus_pending_call_set_timeout_added_unlocked (pending, FALSE);
    }


  _dbus_connection_ref_unlocked (connection);
  _dbus_pending_call_unref_and_unlock (pending);
  CONNECTION_LOCK (connection);
  _dbus_connection_unref_unlocked (connection);
}
