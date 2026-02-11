update_account_uri_schemes (TpawAccountSettings *self)
{
  if (self->priv->uri_scheme_tel == account_has_uri_scheme_tel (
        self->priv->account))
    return;

  tp_account_set_uri_scheme_association_async (self->priv->account, "tel",
      self->priv->uri_scheme_tel, NULL, NULL);
}
