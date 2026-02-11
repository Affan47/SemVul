fs_rtp_bitrate_adapter_getcaps (FsRtpBitrateAdapter *self, GstPad *pad,
    GstCaps *filter)
{
  GstCaps *caps;
  GstPad *otherpad;
  GstCaps *peer_caps;

  if (pad == self->srcpad)
    otherpad = self->sinkpad;
  else
    otherpad = self->srcpad;

  peer_caps = gst_pad_peer_query_caps (otherpad, filter);

  GST_OBJECT_LOCK (self);
  if (self->caps)
    caps = gst_caps_intersect_full (self->caps, peer_caps,
        GST_CAPS_INTERSECT_FIRST);
  else
    caps = gst_caps_intersect (peer_caps,
        gst_pad_get_pad_template_caps (pad));
  gst_caps_unref (peer_caps);
  GST_OBJECT_UNLOCK (self);

  return caps;
}
