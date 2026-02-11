gst_controller_suggest_next_sync (GstController * self)
{
  GstClockTime ret;

  g_return_val_if_fail (GST_IS_CONTROLLER (self), GST_CLOCK_TIME_NONE);
  g_return_val_if_fail (self->priv->control_rate != GST_CLOCK_TIME_NONE,
      GST_CLOCK_TIME_NONE);

  g_mutex_lock (self->lock);


  ret = self->priv->last_sync + self->priv->control_rate;

  g_mutex_unlock (self->lock);

  return ret;
}
