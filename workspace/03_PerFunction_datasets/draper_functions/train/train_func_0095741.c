irtty_chars_in_buffer(struct sir_dev *dev)
{
	struct sirtty_cb *priv = dev->priv;

	IRDA_ASSERT(priv != NULL, return -1;);
	IRDA_ASSERT(priv->magic == IRTTY_MAGIC, return -1;);

	return tty_chars_in_buffer(priv->tty);
}
