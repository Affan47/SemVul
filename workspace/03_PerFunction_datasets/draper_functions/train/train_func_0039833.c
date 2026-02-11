goa_telepathy_provider_finalize (GObject *object)
{
  GoaTelepathyProviderPrivate *priv = GOA_TELEPATHY_PROVIDER (object)->priv;

  g_clear_object (&priv->protocol);
  g_free (priv->protocol_name);
  g_free (priv->provider_type);

  (G_OBJECT_CLASS (goa_telepathy_provider_parent_class)->finalize) (object);
}
