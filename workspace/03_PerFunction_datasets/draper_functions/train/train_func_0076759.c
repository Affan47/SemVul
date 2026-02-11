gdome_evt_mevnt_relatedNode (GdomeMutationEvent *self, GdomeException *exc)
{
  Gdome_evt_MutationEvent *priv = (Gdome_evt_MutationEvent *)self;

  g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (exc != NULL, NULL);
	if (priv->relatedNode != NULL) gdome_n_ref(priv->relatedNode, exc);

  return priv->relatedNode;
}
