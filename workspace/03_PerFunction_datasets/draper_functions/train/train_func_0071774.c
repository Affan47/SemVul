dbus_message_set_reply_serial (DBusMessage   *message,
                               dbus_uint32_t  reply_serial)
{
  _dbus_return_val_if_fail (message != NULL, FALSE);
  _dbus_return_val_if_fail (!message->locked, FALSE);
  _dbus_return_val_if_fail (reply_serial != 0, FALSE);

  return _dbus_header_set_field_basic (&message->header,
                                       DBUS_HEADER_FIELD_REPLY_SERIAL,
                                       DBUS_TYPE_UINT32,
                                       &reply_serial);
}
