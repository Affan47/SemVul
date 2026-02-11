tp_base_connection_manager_register (TpBaseConnectionManager *self)
{
  GError *error = NULL;
  TpBaseConnectionManagerClass *cls;
  GString *string = NULL;
  guint i;
  GHashTableIter iter;
  gpointer name, protocol;

  g_assert (TP_IS_BASE_CONNECTION_MANAGER (self));
  cls = TP_BASE_CONNECTION_MANAGER_GET_CLASS (self);

  if (!tp_base_connection_manager_ensure_dbus (self, &error))
    goto except;

  if (cls->protocol_params != NULL)
    {
      for (i = 0; cls->protocol_params[i].name != NULL; i++)
        {
          TpBaseProtocol *p = _tp_legacy_protocol_new (self,
              cls->protocol_params + i);

          tp_base_connection_manager_add_protocol (self, p);
          g_object_unref (p);
        }
    }

  g_assert (self->priv->dbus_daemon != NULL);

  string = g_string_new (TP_CM_BUS_NAME_BASE);
  g_string_append (string, cls->cm_dbus_name);

  if (!tp_dbus_daemon_request_name (self->priv->dbus_daemon, string->str,
        TRUE, &error))
    goto except;

  g_string_assign (string, TP_CM_OBJECT_PATH_BASE);
  g_string_append (string, cls->cm_dbus_name);
  tp_dbus_daemon_register_object (self->priv->dbus_daemon, string->str, self);

  g_hash_table_iter_init (&iter, self->priv->protocols);

  while (g_hash_table_iter_next (&iter, &name, &protocol))
    {
      TpBaseProtocolClass *protocol_class =
        TP_BASE_PROTOCOL_GET_CLASS (protocol);

      if (!tp_connection_manager_check_valid_protocol_name (name, &error))
        {
          g_critical ("%s", error->message);
          goto except;
        }


      if (protocol_class->is_stub)
        continue;

      g_string_assign (string, TP_CM_OBJECT_PATH_BASE);
      g_string_append (string, cls->cm_dbus_name);
      g_string_append_c (string, '/');
      g_string_append (string, name);

      g_strdelimit (string->str, "-", '_');

      tp_dbus_daemon_register_object (self->priv->dbus_daemon, string->str,
          protocol);
    }

  g_string_free (string, TRUE);

  self->priv->registered = TRUE;

  return TRUE;

except:
  WARNING ("Couldn't claim bus name. If you are trying to debug this "
      "connection manager, disable all accounts and kill any running "
      "copies of this CM, then try again. %s", error->message);
  g_error_free (error);

  if (string != NULL)
    g_string_free (string, TRUE);

  return FALSE;
}
