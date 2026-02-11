_tp_account_manager_account_enabled_cb (TpAccount *account,
    GParamSpec *spec,
    gpointer manager)
{
  TpAccountManager *self = TP_ACCOUNT_MANAGER (manager);

  if (tp_account_is_enabled (account))
    g_signal_emit (self, signals[ACCOUNT_ENABLED], 0, account);
  else
    g_signal_emit (self, signals[ACCOUNT_DISABLED], 0, account);
}
