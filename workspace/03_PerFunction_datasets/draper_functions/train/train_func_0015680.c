gst_pad_remove_data_probe (GstPad * pad, guint handler_id)
{
  g_return_if_fail (GST_IS_PAD (pad));
  g_return_if_fail (handler_id > 0);

  GST_OBJECT_LOCK (pad);
  g_signal_handler_disconnect (pad, handler_id);
  GST_PAD_DO_BUFFER_SIGNALS (pad)--;
  GST_PAD_DO_EVENT_SIGNALS (pad)--;
  GST_CAT_DEBUG_OBJECT (GST_CAT_PADS, pad,
      "removed data probe, now %d event, %d buffer probes",
      GST_PAD_DO_EVENT_SIGNALS (pad), GST_PAD_DO_BUFFER_SIGNALS (pad));
  GST_OBJECT_UNLOCK (pad);

}
