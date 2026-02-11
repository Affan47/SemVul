tp_connection_get_balance (TpConnection *self,
    gint *balance,
    guint *scale,
    const gchar **currency)
{
  g_return_val_if_fail (TP_IS_CONNECTION (self), FALSE);

  if (self->priv->balance_currency == NULL)
    return FALSE;

  if (self->priv->balance == 0 &&
      self->priv->balance_scale == G_MAXUINT32 &&
      tp_str_empty (self->priv->balance_currency))
    return FALSE;

  if (balance != NULL)
    *balance = self->priv->balance;

  if (scale != NULL)
    *scale = self->priv->balance_scale;

  if (currency != NULL)
    *currency = self->priv->balance_currency;

  return TRUE;
}
