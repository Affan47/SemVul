tp_capabilities_constructed (GObject *object)
{
  void (*chain_up) (GObject *) =
    ((GObjectClass *) tp_capabilities_parent_class)->constructed;
  TpCapabilities *self = TP_CAPABILITIES (object);

  g_assert (self->priv->classes != NULL);

  if (chain_up != NULL)
    chain_up (object);
}
