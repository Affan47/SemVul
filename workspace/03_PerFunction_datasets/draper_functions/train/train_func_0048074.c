tp_account_request_set_requested_presence (TpAccountRequest *self,
    TpConnectionPresenceType presence,
    const gchar *status,
    const gchar *message)
{
  TpAccountRequestPrivate *priv;
  GValue *value;
  GValueArray *arr;

  g_return_if_fail (TP_IS_ACCOUNT_REQUEST (self));

  priv = self->priv;

  g_return_if_fail (priv->result == NULL && !priv->created);

  value = tp_g_value_slice_new_take_boxed (TP_STRUCT_TYPE_SIMPLE_PRESENCE,
      dbus_g_type_specialized_construct (TP_STRUCT_TYPE_SIMPLE_PRESENCE));
  arr = (GValueArray *) g_value_get_boxed (value);

  g_value_set_uint (arr->values, presence);
  g_value_set_string (arr->values + 1, status);
  g_value_set_string (arr->values + 2, message);

  g_hash_table_insert (priv->properties,
      TP_PROP_ACCOUNT_REQUESTED_PRESENCE, value);
}
