dbus_message_is_signal (DBusMessage *message,
                        const char  *iface,
                        const char  *signal_name)
{
  _dbus_return_val_if_fail (message != NULL, FALSE);
  _dbus_return_val_if_fail (iface != NULL, FALSE);
  _dbus_return_val_if_fail (signal_name != NULL, FALSE);


  return _dbus_message_has_type_interface_member (message,
                                                  DBUS_MESSAGE_TYPE_SIGNAL,
                                                  iface, signal_name);
}
