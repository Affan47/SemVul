fs_rtp_bitrate_adapter_getcaps (GstPad *pad)
{
  FsRtpBitrateAdapter *self = FS_RTP_BITRATE_ADAPTER (
    gst_pad_get_parent_element (pad));
  GstCaps *caps;
  GstPad *otherpad;
  GstCaps *peer_caps;

  if (!self)
    return gst_caps_new_empty ();

  if (pad == self->srcpad)
    otherpad = self->sinkpad;
  else
    otherpad = self->srcpad;

  peer_caps = gst_pad_peer_get_caps_reffed (otherpad);

  GST_OBJECT_LOCK (self);
  if (peer_caps)
  {
    if (self->caps)
      caps = gst_caps_intersect_full (self->caps, peer_caps,
          GST_CAPS_INTERSECT_FIRST);
    else
      caps = gst_caps_intersect (peer_caps,
          gst_pad_get_pad_template_caps (pad));

      gst_caps_unref (peer_caps);
  }
  else
  {
    if (self->caps)
      caps = gst_caps_intersect (self->caps,
          gst_pad_get_pad_template_caps (pad));
    else
      caps = gst_caps_copy (gst_pad_get_pad_template_caps (pad));
  }
  GST_OBJECT_UNLOCK (self);

  gst_object_unref (self);

  return caps;
}
