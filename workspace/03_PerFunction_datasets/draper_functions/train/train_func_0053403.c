tpaw_account_settings_constructed (GObject *object)
{
  TpawAccountSettings *self = TPAW_ACCOUNT_SETTINGS (object);

  if (self->priv->account != NULL)
    {
      g_free (self->priv->cm_name);
      g_free (self->priv->protocol);
      g_free (self->priv->service);

      self->priv->cm_name =
        g_strdup (tp_account_get_cm_name (self->priv->account));
      self->priv->protocol =
        g_strdup (tp_account_get_protocol_name (self->priv->account));
      self->priv->service =
        g_strdup (tp_account_get_service (self->priv->account));
      self->priv->icon_name = g_strdup
        (tp_account_get_icon_name (self->priv->account));
    }
  else
    {
      self->priv->icon_name = tpaw_protocol_icon_name (self->priv->protocol);
    }

  g_assert (self->priv->cm_name != NULL && self->priv->protocol != NULL);

  tpaw_account_settings_check_readyness (self);

  if (!self->priv->ready)
    {
      GQuark features[] = {
          TP_ACCOUNT_FEATURE_CORE,
          TP_ACCOUNT_FEATURE_STORAGE,
          TP_ACCOUNT_FEATURE_ADDRESSING,
          0 };

      if (self->priv->account != NULL)
        {
          tp_proxy_prepare_async (self->priv->account, features,
              tpaw_account_settings_account_ready_cb, self);
        }

      tp_g_signal_connect_object (self->priv->managers, "notify::ready",
        G_CALLBACK (tpaw_account_settings_managers_ready_cb), object, 0);
    }

  if (G_OBJECT_CLASS (
        tpaw_account_settings_parent_class)->constructed != NULL)
    G_OBJECT_CLASS (
        tpaw_account_settings_parent_class)->constructed (object);
}
