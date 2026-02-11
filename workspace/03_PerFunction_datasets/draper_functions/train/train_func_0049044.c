gst_tee_push_eos (GstPad * pad, GstTee * tee)
{
  if (pad != tee->pull_pad)
    gst_pad_push_event (pad, gst_event_new_eos ());
  gst_object_unref (pad);
}
