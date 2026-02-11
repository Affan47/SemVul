gst_input_selector_block (GstInputSelector * self)
{
  gint64 ret = 0;
  GstSelectorPad *spad;

  GST_INPUT_SELECTOR_LOCK (self);

  if (self->blocked)
    GST_WARNING_OBJECT (self, "switch already blocked");

  self->blocked = TRUE;
  spad = GST_SELECTOR_PAD_CAST (self->active_sinkpad);

  if (spad)
    ret = gst_selector_pad_get_running_time (spad);
  else
    GST_DEBUG_OBJECT (self, "no active pad while blocking");

  GST_INPUT_SELECTOR_UNLOCK (self);

  return ret;
}
