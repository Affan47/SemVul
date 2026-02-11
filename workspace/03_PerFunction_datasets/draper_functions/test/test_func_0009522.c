tp_base_connection_disconnect_with_dbus_error (TpBaseConnection *self,
                                               const gchar *error_name,
                                               GHashTable *details,
                                               TpConnectionStatusReason reason)
{
  GHashTable *dup_ = NULL;

  g_return_if_fail (TP_IS_BASE_CONNECTION (self));
  g_return_if_fail (tp_dbus_check_valid_interface_name (error_name, NULL));

  if (details == NULL)
    {
      dup_ = g_hash_table_new (g_str_hash, g_str_equal);
      details = dup_;
    }

  tp_svc_connection_emit_connection_error (self, error_name, details);
  tp_base_connection_change_status (self, TP_CONNECTION_STATUS_DISCONNECTED,
      reason);

  if (dup_ != NULL)
    g_hash_table_unref (dup_);
}
