pk_progress_bar_finalize (GObject *object)
{
	PkProgressBar *self;
	g_return_if_fail (PK_IS_PROGRESS_BAR (object));
	self = PK_PROGRESS_BAR (object);

	if (self->priv->timer_id != 0)
		g_source_remove (self->priv->timer_id);
	if (self->priv->tty_fd > 0)
		close (self->priv->tty_fd);
	G_OBJECT_CLASS (pk_progress_bar_parent_class)->finalize (object);
}
