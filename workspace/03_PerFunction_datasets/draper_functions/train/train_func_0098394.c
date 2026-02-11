gst_rtp_depay_getcaps (GstPad * pad)
{
  GstRTPDepay *src;
  GstPad *other;
  GstCaps *caps;

  src = GST_RTP_DEPAY (GST_PAD_PARENT (pad));

  other = pad == src->src_rtp ? src->sink_rtp : src->src_rtp;

  caps = gst_pad_peer_get_caps (other);

  if (caps == NULL)
    caps = gst_caps_copy (gst_pad_get_pad_template_caps (pad));

  return caps;
}
