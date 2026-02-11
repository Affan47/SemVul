gst_bin_state_changed (GstElement * element, GstState oldstate,
    GstState newstate, GstState pending)
{
  GstElementClass *pklass = (GstElementClass *) parent_class;

  if (newstate == GST_STATE_PLAYING && pending == GST_STATE_VOID_PENDING)
    bin_do_eos (GST_BIN_CAST (element));

  if (pklass->state_changed)
    pklass->state_changed (element, oldstate, newstate, pending);
}
