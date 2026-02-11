gst_input_selector_wait (RsnInputSelector * self, RsnSelectorPad * pad)
{
  while (self->blocked && !self->flushing && !pad->flushing) {


    GST_INPUT_SELECTOR_WAIT (self);
  }
  return self->flushing;
}
