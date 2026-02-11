update_account_service (TpawAccountSettings *self)
{
  if (!self->priv->update_service)
    return;

  tp_account_set_service_async (self->priv->account,
      self->priv->service != NULL ? self->priv->service : "",
      set_service_cb, self);
}
