wait_and_drop_eos_cb (GstPad * pad, GstPadProbeInfo * info, gpointer user_data)
{
  GstPad *peer;

  if (GST_EVENT_TYPE (GST_PAD_PROBE_INFO_EVENT (info)) != GST_EVENT_EOS)
    return GST_PAD_PROBE_PASS;

  peer = gst_pad_get_peer (pad);
  if (peer) {
    gst_pad_unlink (pad, peer);
    gst_object_unref (peer);
  }

  return GST_PAD_PROBE_DROP;
}
