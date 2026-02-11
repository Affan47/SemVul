unschedule_current_timer (GstRtpJitterBuffer * jitterbuffer)
{
  GstRtpJitterBufferPrivate *priv = jitterbuffer->priv;

  if (priv->clock_id) {
    GST_DEBUG_OBJECT (jitterbuffer, "unschedule current timer");
    gst_clock_id_unschedule (priv->clock_id);
    priv->clock_id = NULL;
  }
}
