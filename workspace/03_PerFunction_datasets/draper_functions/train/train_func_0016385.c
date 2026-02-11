_atspi_dbus_send_with_reply_and_block (DBusMessage *message, GError **error)
{
  DBusMessage *reply;
  DBusError err;
  AtspiApplication *app;
  DBusConnection *bus;

  app = get_application (dbus_message_get_destination (message));

  if (app && !app->bus)
    return NULL;

  bus = (app ? app->bus : _atspi_bus());
  dbus_error_init (&err);
  set_timeout (app);
  reply = dbind_send_and_allow_reentry (bus, message, &err);
  process_deferred_messages ();
  dbus_message_unref (message);
  if (dbus_error_is_set (&err))
  {
    if (error)
      g_set_error_literal (error, ATSPI_ERROR, ATSPI_ERROR_IPC, err.message);
    dbus_error_free (&err);
  }
  return reply;
}
