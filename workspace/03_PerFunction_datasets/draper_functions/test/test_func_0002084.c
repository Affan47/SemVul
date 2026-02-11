dbus_message_iter_next (DBusMessageIter *iter)
{
  DBusMessageRealIter *real = (DBusMessageRealIter *)iter;

  _dbus_return_val_if_fail (_dbus_message_iter_check (real), FALSE);
  _dbus_return_val_if_fail (real->iter_type == DBUS_MESSAGE_ITER_TYPE_READER, FALSE);

  return _dbus_type_reader_next (&real->u.reader);
}
