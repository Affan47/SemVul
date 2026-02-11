clocks_timer_countdown_frame_reset (ClocksTimerCountdownFrame* self) {
	g_return_if_fail (self != NULL);
	self->priv->elapsed_before_pause = (gdouble) 0;
	self->priv->elapsed = (gdouble) 0;
}
