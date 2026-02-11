tp_account_request_set_parameter (TpAccountRequest *self,
    const gchar *key,
    GVariant *value)
{
  TpAccountRequestPrivate *priv;
  GValue one = G_VALUE_INIT, *two;

  g_return_if_fail (TP_IS_ACCOUNT_REQUEST (self));
  g_return_if_fail (key != NULL);
  g_return_if_fail (value != NULL);

  priv = self->priv;

  g_return_if_fail (priv->result == NULL && !priv->created);

  dbus_g_value_parse_g_variant (value, &one);
  two = tp_g_value_slice_dup (&one);

  g_hash_table_insert (priv->parameters, g_strdup (key), two);

  g_value_unset (&one);
}
