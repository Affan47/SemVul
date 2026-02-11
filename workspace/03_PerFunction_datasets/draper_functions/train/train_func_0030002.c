tp_contact_dup_location (TpContact *self)
{
  g_return_val_if_fail (self != NULL, NULL);

  if (self->priv->location == NULL)
    return NULL;

  return _tp_asv_to_vardict (self->priv->location);
}
