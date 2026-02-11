dbus_message_set_serial (DBusMessage   *message,
                         dbus_uint32_t  serial)
{
  _dbus_return_if_fail (message != NULL);
  _dbus_return_if_fail (!message->locked);

  _dbus_header_set_serial (&message->header, serial);
}
