dbus_g_method_send_reply (DBusGMethodInvocation *context, DBusMessage *reply)
{
  g_return_if_fail (context != NULL);
  g_return_if_fail (reply != NULL);

  connection_send_or_die (dbus_g_connection_get_connection (context->connection),
      reply);
  dbus_message_unref (reply);

  dbus_g_connection_unref (context->connection);
  dbus_g_message_unref (context->message);
  g_free (context);
}
