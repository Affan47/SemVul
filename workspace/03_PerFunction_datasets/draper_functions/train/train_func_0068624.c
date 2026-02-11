irtty_do_write(struct sir_dev *dev, const unsigned char *ptr, size_t len)
{
	struct sirtty_cb *priv = dev->priv;
	struct tty_struct *tty;
	int writelen;

	IRDA_ASSERT(priv != NULL, return -1;);
	IRDA_ASSERT(priv->magic == IRTTY_MAGIC, return -1;);

	tty = priv->tty;
	if (!tty->ops->write)
		return 0;
	set_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);
	writelen = tty_write_room(tty);
	if (writelen > len)
		writelen = len;
	return tty->ops->write(tty, ptr, writelen);
}
