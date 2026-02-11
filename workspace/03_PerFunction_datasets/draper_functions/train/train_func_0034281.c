gst_tuner_signal_changed (GstTuner * tuner,
    GstTunerChannel * channel, gint signal)
{
  g_return_if_fail (GST_IS_TUNER (tuner));
  g_return_if_fail (GST_IS_TUNER_CHANNEL (channel));

  g_signal_emit (G_OBJECT (tuner),
      gst_tuner_signals[SIGNAL_CHANGED], 0, channel, signal);

  g_signal_emit_by_name (G_OBJECT (channel), "signal_changed", signal);
}
