tpaw_account_settings_has_account (TpawAccountSettings *settings,
    TpAccount *account)
{
  const gchar *account_path;
  const gchar *priv_account_path;

  g_return_val_if_fail (TPAW_IS_ACCOUNT_SETTINGS (settings), FALSE);
  g_return_val_if_fail (TP_IS_ACCOUNT (account), FALSE);

  if (settings->priv->account == NULL)
    return FALSE;

  account_path = tp_proxy_get_object_path (TP_PROXY (account));
  priv_account_path = tp_proxy_get_object_path (
      TP_PROXY (settings->priv->account));

  return (!tp_strdiff (account_path, priv_account_path));
}
