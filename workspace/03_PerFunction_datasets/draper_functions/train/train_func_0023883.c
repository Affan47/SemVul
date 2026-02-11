dbus_pending_call_ref (DBusPendingCall *pending)
{
  dbus_int32_t old_refcount;

  _dbus_return_val_if_fail (pending != NULL, NULL);

  old_refcount = _dbus_atomic_inc (&pending->refcount);
  _dbus_pending_call_trace_ref (pending, old_refcount, old_refcount + 1,
      "ref");

  return pending;
}
