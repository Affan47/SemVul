gconf_engine_set (GConfEngine* conf, const gchar* key,
                  const GConfValue* value, GError** err)
{
  const gchar *db;
  DBusMessage *message, *reply;
  DBusError error;
  DBusMessageIter iter;

  g_return_val_if_fail(conf != NULL, FALSE);
  g_return_val_if_fail(key != NULL, FALSE);
  g_return_val_if_fail(value != NULL, FALSE);
  g_return_val_if_fail(value->type != GCONF_VALUE_INVALID, FALSE);
  g_return_val_if_fail( (value->type != GCONF_VALUE_STRING) ||
                        (gconf_value_get_string(value) != NULL) , FALSE );
  g_return_val_if_fail( (value->type != GCONF_VALUE_LIST) ||
                        (gconf_value_get_list_type(value) != GCONF_VALUE_INVALID), FALSE);
  g_return_val_if_fail(err == NULL || *err == NULL, FALSE);

  CHECK_OWNER_USE (conf);

  if (!gconf_key_check (key, err))
    return FALSE;

  if (!gconf_value_validate (value, err))
    return FALSE;

  if (gconf_engine_is_local (conf))
    {
      GError* error = NULL;

      gconf_sources_set_value (conf->local_sources, key, value, NULL, &error);

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

  db = gconf_engine_get_database (conf, TRUE, err);

  if (db == NULL)
    {
      g_return_val_if_fail(err == NULL || *err != NULL, FALSE);

      return FALSE;
    }

  message = dbus_message_new_method_call (GCONF_DBUS_SERVICE,
					  db,
					  GCONF_DBUS_DATABASE_INTERFACE,
					  GCONF_DBUS_DATABASE_SET);

  dbus_message_append_args (message,
			    DBUS_TYPE_STRING, &key,
			    DBUS_TYPE_INVALID);

  dbus_message_iter_init_append (message, &iter);
  gconf_dbus_utils_append_value (&iter, value);

  dbus_error_init (&error);
  reply = dbus_connection_send_with_reply_and_block (global_conn, message, -1, &error);
  dbus_message_unref (message);

  if (gconf_handle_dbus_exception (reply, &error, err))
    return FALSE;

  g_return_val_if_fail (err == NULL || *err == NULL, FALSE);

  dbus_message_unref (reply);

  return TRUE;
}
