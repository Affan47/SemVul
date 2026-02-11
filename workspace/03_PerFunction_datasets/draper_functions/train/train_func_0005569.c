database_handle_get_all_dirs (DBusConnection *conn,
                              DBusMessage    *message,
                              GConfDatabase  *db)
{
  GSList          *dirs, *l;
  gchar           *dir;
  GError          *gerror = NULL;
  DBusMessage     *reply;
  DBusMessageIter  iter;
  DBusMessageIter  array_iter;

  if (!gconfd_dbus_get_message_args (conn, message,
				     DBUS_TYPE_STRING, &dir,
				     DBUS_TYPE_INVALID))
    return;

  dirs = gconf_database_all_dirs (db, dir, &gerror);

  if (gconfd_dbus_set_exception (conn, message, &gerror))
    return;

  reply = dbus_message_new_method_return (message);

  dbus_message_iter_init_append (reply, &iter);

  dbus_message_iter_open_container (&iter,
				    DBUS_TYPE_ARRAY,
				    DBUS_TYPE_STRING_AS_STRING,
				    &array_iter);

  for (l = dirs; l; l = l->next)
    {
      gchar *str = (gchar *) l->data;

      dbus_message_iter_append_basic (&array_iter,
				      DBUS_TYPE_STRING,
				      &str);

      g_free (l->data);
    }

  dbus_message_iter_close_container (&iter, &array_iter);

  g_slist_free (dirs);

  dbus_connection_send (conn, reply, NULL);
  dbus_message_unref (reply);
}
