database_handle_suggest_sync (DBusConnection *conn,
		              DBusMessage    *message,
		              GConfDatabase  *db)
{
  GError *gerror = NULL;
  DBusMessage *reply;

  gconf_database_sync (db, &gerror);

  if (gconfd_dbus_set_exception (conn, message, &gerror))
    return;

  reply = dbus_message_new_method_return (message);
  dbus_connection_send (conn, reply, NULL);
  dbus_message_unref (reply);
}
