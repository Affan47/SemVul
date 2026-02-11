gst_rtp_mux_release_pad (GstElement * element, GstPad * pad)
{
  GstRTPMuxPadPrivate *padpriv;

  GST_OBJECT_LOCK (element);
  padpriv = gst_pad_get_element_private (pad);
  gst_pad_set_element_private (pad, NULL);
  GST_OBJECT_UNLOCK (element);

  gst_element_remove_pad (element, pad);

  if (padpriv) {
    gst_caps_replace (&padpriv->out_caps, NULL);
    g_slice_free (GstRTPMuxPadPrivate, padpriv);
  }
}
