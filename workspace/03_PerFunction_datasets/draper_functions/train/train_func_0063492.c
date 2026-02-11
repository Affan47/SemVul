dbus_message_iter_close_container (DBusMessageIter *iter,
                                   DBusMessageIter *sub)
{
  DBusMessageRealIter *real = (DBusMessageRealIter *)iter;
  DBusMessageRealIter *real_sub = (DBusMessageRealIter *)sub;
  dbus_bool_t ret;

  _dbus_return_val_if_fail (_dbus_message_iter_append_check (real), FALSE);
  _dbus_return_val_if_fail (real->iter_type == DBUS_MESSAGE_ITER_TYPE_WRITER, FALSE);
  _dbus_return_val_if_fail (_dbus_message_iter_append_check (real_sub), FALSE);
  _dbus_return_val_if_fail (real_sub->iter_type == DBUS_MESSAGE_ITER_TYPE_WRITER, FALSE);

  ret = _dbus_type_writer_unrecurse (&real->u.writer,
                                     &real_sub->u.writer);

  if (!_dbus_message_iter_close_signature (real))
    ret = FALSE;

  return ret;
}
