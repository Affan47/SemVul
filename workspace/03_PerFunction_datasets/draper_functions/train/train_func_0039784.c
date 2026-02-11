ping() {
  DBusConnection *con;
  DBusMessage *msg, *res;
  DBusError error;
  dbus_error_init(&error);
  const char *_ping = PING;

  con = dbus_bus_get(DBUS_BUS_SESSION, &error);
  if (!con) {
    std::cerr << error.message << std::endl;
    dbus_error_free(&error);
    return false;
  }
  msg = dbus_message_new_method_call (BUS_NAME, BUS_PATH, BUS_NAME, PING);
  dbus_message_set_auto_start(msg, FALSE);

  dbus_message_append_args(msg, DBUS_TYPE_STRING, &_ping, DBUS_TYPE_INVALID);
  res = dbus_connection_send_with_reply_and_block(con, msg, 2000, &error);
  dbus_message_unref(msg);
  if (res == NULL) {
    std::cerr << error.message << std::endl;
    dbus_error_free(&error);
    return false;
  }

  if (dbus_message_get_type (res) == DBUS_MESSAGE_TYPE_ERROR) {
    dbus_set_error_from_message(&error, res);
    std::cerr << error.message << std::endl;
    dbus_message_unref (res);
    dbus_error_free (&error);
    return false;
  }


  dbus_message_unref(res);
  return true;
}
