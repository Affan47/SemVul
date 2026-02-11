sbc_reinit(sbc_t *sbc, unsigned long flags)
{
	struct sbc_priv *priv;

	if (!sbc || !sbc->priv)
		return -EIO;

	priv = sbc->priv;

	if (priv->init == 1)
		memset(sbc->priv, 0, sizeof(struct sbc_priv));

	sbc_set_defaults(sbc, flags);

	return 0;
}
