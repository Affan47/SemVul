gconf_engine_recursive_unset (GConfEngine    *conf,
                              const char     *key,
                              GConfUnsetFlags flags,
                              GError        **err)
{
  const gchar *db;
  DBusMessage *message, *reply;
  DBusError error;
  guint dbus_flags;
  const gchar *empty;

  g_return_val_if_fail (conf != NULL, FALSE);
  g_return_val_if_fail (key != NULL, FALSE);
  g_return_val_if_fail (err == NULL || *err == NULL, FALSE);

  CHECK_OWNER_USE (conf);

  if (!gconf_key_check (key, err))
    return FALSE;

  if (gconf_engine_is_local (conf))
    {
      GError* error = NULL;

      gconf_sources_recursive_unset (conf->local_sources, key, NULL,
                                     flags, NULL, &error);

      if (error != NULL)
        {
          if (err)
            *err = error;
          else
            {
              g_error_free (error);
            }
          return FALSE;
        }

      return TRUE;
    }

  g_assert (!gconf_engine_is_local (conf));

  dbus_flags = 0;
  if (flags & GCONF_UNSET_INCLUDING_SCHEMA_NAMES)
    dbus_flags |= GCONF_DBUS_UNSET_INCLUDING_SCHEMA_NAMES;

  db = gconf_engine_get_database (conf, TRUE, err);

  if (db == NULL)
    {
      g_return_val_if_fail (err == NULL || *err != NULL, FALSE);

      return FALSE;
    }

  message = dbus_message_new_method_call (GCONF_DBUS_SERVICE,
					  db,
					  GCONF_DBUS_DATABASE_INTERFACE,
					  GCONF_DBUS_DATABASE_RECURSIVE_UNSET);

  empty = "";
  dbus_message_append_args (message,
			    DBUS_TYPE_STRING, &key,
			    DBUS_TYPE_STRING, &empty,
			    DBUS_TYPE_UINT32, &dbus_flags,
			    DBUS_TYPE_INVALID);

  dbus_error_init (&error);
  reply = dbus_connection_send_with_reply_and_block (global_conn, message, -1, &error);
  dbus_message_unref (message);

  if (gconf_handle_dbus_exception (reply, &error, err))
    return FALSE;

  g_return_val_if_fail (err == NULL || *err == NULL, FALSE);

  dbus_message_unref (reply);

  return TRUE;
}
