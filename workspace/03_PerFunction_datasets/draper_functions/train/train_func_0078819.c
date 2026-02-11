caps_notify_cb (GstPad * pad, GParamSpec * unused, GstPlaySink * playsink)
{
  gboolean reconfigure = FALSE;
  GstCaps *caps;
  gboolean raw;

  g_object_get (pad, "caps", &caps, NULL);
  if (!caps)
    return;

  if (pad == playsink->audio_pad) {
    raw = is_raw_pad (pad);
    reconfigure = (! !playsink->audio_pad_raw != ! !raw)
        && playsink->audiochain;
    GST_DEBUG_OBJECT (pad,
        "Audio caps changed: raw %d reconfigure %d caps %" GST_PTR_FORMAT, raw,
        reconfigure, caps);
  } else if (pad == playsink->video_pad) {
    raw = is_raw_pad (pad);
    reconfigure = (! !playsink->video_pad_raw != ! !raw)
        && playsink->videochain;
    GST_DEBUG_OBJECT (pad,
        "Video caps changed: raw %d reconfigure %d caps %" GST_PTR_FORMAT, raw,
        reconfigure, caps);
  }

  gst_caps_unref (caps);

  if (reconfigure)
    gst_play_sink_reconfigure (playsink);
}
