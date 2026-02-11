brasero_burn_progress_stop_blinking (BraseroBurnProgress *self)
{
	if (self->priv->pulse_id) {
		g_source_remove (self->priv->pulse_id);
		self->priv->pulse_id = 0;

		gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (self->priv->progress),
					       self->priv->current_progress);
	}
}
