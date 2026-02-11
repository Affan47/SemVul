kgdb_nmi_tty_receiver(unsigned long data)
{
	struct kgdb_nmi_tty_priv *priv = (void *)data;
	char ch;

	priv->timer.expires = jiffies + (HZ/100);
	add_timer(&priv->timer);

	if (likely(!atomic_read(&kgdb_nmi_num_readers) ||
		   !kfifo_len(&priv->fifo)))
		return;

	while (kfifo_out(&priv->fifo, &ch, 1))
		tty_insert_flip_char(&priv->port, ch, TTY_NORMAL);
	tty_flip_buffer_push(&priv->port);
}
