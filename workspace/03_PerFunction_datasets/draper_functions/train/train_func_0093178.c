database_handle_dir_exists (DBusConnection *conn,
                            DBusMessage    *message,
                            GConfDatabase  *db)
{
  gboolean     exists;
  gchar       *dir;
  GError      *gerror = NULL;
  DBusMessage *reply;

  if (!gconfd_dbus_get_message_args (conn, message,
				     DBUS_TYPE_STRING, &dir,
				     DBUS_TYPE_INVALID))
    return;

  exists = gconf_database_dir_exists (db, dir, &gerror);

  if (gconfd_dbus_set_exception (conn, message, &gerror))
    return;

  reply = dbus_message_new_method_return (message);
  dbus_message_append_args (reply,
			    DBUS_TYPE_BOOLEAN, &exists,
			    DBUS_TYPE_INVALID);
  dbus_connection_send (conn, reply, NULL);
  dbus_message_unref (reply);
}
