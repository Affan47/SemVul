_tp_account_manager_update_most_available_presence (TpAccountManager *manager)
{
  TpAccountManagerPrivate *priv = manager->priv;
  TpConnectionPresenceType presence = TP_CONNECTION_PRESENCE_TYPE_OFFLINE;
  TpAccount *account = NULL;
  GHashTableIter iter;
  gpointer value;
  TpAccount *has_unset_presence = NULL;


  g_hash_table_iter_init (&iter, priv->accounts);
  while (g_hash_table_iter_next (&iter, NULL, &value))
    {
      TpAccount *a = TP_ACCOUNT (value);
      TpConnectionPresenceType p;

      p = tp_account_get_current_presence (a, NULL, NULL);

      if (p == TP_CONNECTION_PRESENCE_TYPE_UNSET)
        {
          has_unset_presence = a;


          continue;
        }

      if (tp_connection_presence_type_cmp_availability (p, presence) > 0)
        {
          account = a;
          presence = p;
        }
    }

  if (presence == TP_CONNECTION_PRESENCE_TYPE_OFFLINE &&
      has_unset_presence != NULL)
    {


      account = has_unset_presence;
    }

  priv->most_available_account = account;
  g_free (priv->most_available_status);
  g_free (priv->most_available_status_message);

  if (account == NULL)
    {
      priv->most_available_presence = TP_CONNECTION_PRESENCE_TYPE_OFFLINE;
      priv->most_available_status = g_strdup ("offline");
      priv->most_available_status_message = g_strdup ("");
      return;
    }

  priv->most_available_presence = tp_account_get_current_presence (account,
      &(priv->most_available_status), &(priv->most_available_status_message));

  DEBUG ("Updated most available presence to: %s (%d) \"%s\"",
      priv->most_available_status, priv->most_available_presence,
      priv->most_available_status_message);
}
