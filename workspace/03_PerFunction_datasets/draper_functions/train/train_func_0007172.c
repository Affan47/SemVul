gdome_evt_mevnt_attrChange (GdomeMutationEvent *self, GdomeException *exc)
{
	Gdome_evt_MutationEvent *priv = (Gdome_evt_MutationEvent *)self;

  g_return_val_if_fail (self != NULL, 0);
	g_return_val_if_fail (exc != NULL, 0);

  return priv->attrChange;
}
