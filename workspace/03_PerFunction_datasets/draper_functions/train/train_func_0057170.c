goa_account_chat_disabled_changed_cb (GoaAccount         *goa_account,
                                      GParamSpec         *spec,
                                      GoaTpAccountLinker *self)
{
  GoaTpAccountLinkerPrivate *priv = self->priv;
  const gchar *id;
  TpAccount *tp_account;
  gboolean tp_enabled;
  gboolean goa_enabled;

  id = get_id_from_goa_account (goa_account);
  tp_account = g_hash_table_lookup (priv->tp_accounts, id);
  if (tp_account == NULL)
    return;

  goa_enabled = !goa_account_get_chat_disabled (goa_account);
  tp_enabled = tp_account_is_enabled (tp_account);
  if (tp_enabled != goa_enabled)
    {
      goa_info ("The GOA account %s (Telepathy object path: %s) has been %s, "
          "propagating to Telepathy",
          goa_account_get_id (goa_account), id,
          goa_enabled ? "enabled" : "disabled");
      tp_account_set_enabled_async (tp_account, goa_enabled, NULL, NULL);
    }
}
