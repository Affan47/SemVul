cdbus_call_raw(
  unsigned int timeout,
  DBusMessage * request_ptr)
{
  DBusMessage * reply_ptr;

  if (timeout == 0)
  {
    timeout = DBUS_CALL_DEFAULT_TIMEOUT;
  }

  reply_ptr = dbus_connection_send_with_reply_and_block(
    cdbus_g_dbus_connection,
    request_ptr,
    timeout,
    &cdbus_g_dbus_error);
  if (reply_ptr == NULL)
  {
    cdbus_call_last_error_set();
    dbus_error_free(&cdbus_g_dbus_error);
  }

  return reply_ptr;
}
