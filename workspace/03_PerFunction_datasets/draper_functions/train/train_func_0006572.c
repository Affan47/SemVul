database_handle_recursive_unset  (DBusConnection *conn,
                                  DBusMessage    *message,
                                  GConfDatabase  *db)
{
  gchar       *key;
  gchar       *locale;
  GError      *gerror = NULL;
  guint32      unset_flags;
  DBusMessage *reply;

  if (!gconfd_dbus_get_message_args (conn, message,
				     DBUS_TYPE_STRING, &key,
				     DBUS_TYPE_STRING, &locale,
				     DBUS_TYPE_UINT32, &unset_flags,
				     DBUS_TYPE_INVALID))
    return;

  if (locale[0] == '\0')
    {
      locale = NULL;
    }

  gconf_database_recursive_unset (db, key, locale, unset_flags, &gerror);

  gconf_database_sync (db, NULL);

  if (gconfd_dbus_set_exception (conn, message, &gerror))
    return;

  reply = dbus_message_new_method_return (message);
  dbus_connection_send (conn, reply, NULL);
  dbus_message_unref (reply);
}
