tpaw_account_settings_do_create_account (TpawAccountSettings *self)
{
  TpAccountRequest *account_req;
  GHashTableIter iter;
  gpointer k, v;

  account_req = tp_account_request_new (self->priv->account_manager,
      self->priv->cm_name, self->priv->protocol, "New Account");

  tp_account_request_set_icon_name (account_req, self->priv->icon_name);

  tp_account_request_set_display_name (account_req,
      self->priv->display_name);

  if (self->priv->service != NULL)
    tp_account_request_set_service (account_req, self->priv->service);

  g_hash_table_iter_init (&iter, self->priv->parameters);
  while (g_hash_table_iter_next (&iter, &k, &v))
    {
      const gchar *key = k;
      GVariant *value = v;

      tp_account_request_set_parameter (account_req, key, value);
    }

  if (self->priv->storage_provider != NULL)
    {
      tp_account_request_set_storage_provider (account_req,
          self->priv->storage_provider);
    }

  tp_account_request_create_account_async (account_req,
      tpaw_account_settings_created_cb, self);
}
