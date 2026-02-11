pk_progress_bar_set_percentage (PkProgressBar *self, gint percentage)
{
	g_return_val_if_fail (PK_IS_PROGRESS_BAR (self), FALSE);
	g_return_val_if_fail (percentage <= PK_PROGRESS_BAR_PERCENTAGE_INVALID, FALSE);


	if (self->priv->percentage == G_MININT)
		pk_progress_bar_start (self, "FIXME: need to call pk_progress_bar_start() earlier!");


	if (percentage == self->priv->percentage) {
		g_debug ("skipping as the same");
		goto out;
	}


	self->priv->percentage = percentage;


	if (percentage < 0 || percentage > 100) {
		pk_progress_bar_draw (self, 0);
		pk_progress_bar_draw_pulse_bar (self);
	} else {
		if (self->priv->timer_id != 0) {
			g_source_remove (self->priv->timer_id);
			self->priv->timer_id = 0;
		}
		pk_progress_bar_draw (self, percentage);
	}
out:
	return TRUE;
}
