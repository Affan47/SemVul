pk_progress_bar_init (PkProgressBar *self)
{
	self->priv = PK_PROGRESS_BAR_GET_PRIVATE (self);

	self->priv->size = 10;
	self->priv->percentage = G_MININT;
	self->priv->padding = 0;
	self->priv->timer_id = 0;
	self->priv->tty_fd = open ("/dev/tty", O_RDWR, 0);
	if (self->priv->tty_fd < 0)
		self->priv->tty_fd = open ("/dev/console", O_RDWR, 0);
	if (self->priv->tty_fd < 0)
		self->priv->tty_fd = open ("/dev/stdout", O_RDWR, 0);
	g_assert (self->priv->tty_fd > 0);
}
