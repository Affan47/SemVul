gst_videomixer2_release_pad (GstElement * element, GstPad * pad)
{
  GstVideoMixer2 *mix = NULL;
  GstVideoMixer2Pad *mixpad;
  gboolean update_caps;

  mix = GST_VIDEO_MIXER2 (element);

  GST_VIDEO_MIXER2_LOCK (mix);
  if (G_UNLIKELY (g_slist_find (mix->sinkpads, pad) == NULL)) {
    g_warning ("Unknown pad %s", GST_PAD_NAME (pad));
    goto error;
  }

  mixpad = GST_VIDEO_MIXER2_PAD (pad);

  if (mixpad->convert)
    videomixer_videoconvert_convert_free (mixpad->convert);

  mix->sinkpads = g_slist_remove (mix->sinkpads, pad);
  gst_child_proxy_child_removed (GST_CHILD_PROXY (mix), G_OBJECT (mixpad),
      GST_OBJECT_NAME (mixpad));
  mix->numpads--;

  GST_COLLECT_PADS_STREAM_LOCK (mix->collect);
  gst_videomixer2_update_converters (mix);
  GST_COLLECT_PADS_STREAM_UNLOCK (mix->collect);

  update_caps = GST_VIDEO_INFO_FORMAT (&mix->info) != GST_VIDEO_FORMAT_UNKNOWN;
  GST_VIDEO_MIXER2_UNLOCK (mix);

  gst_collect_pads_remove_pad (mix->collect, pad);

  if (update_caps)
    gst_videomixer2_update_src_caps (mix);

  gst_element_remove_pad (element, pad);
  return;
error:
  GST_VIDEO_MIXER2_UNLOCK (mix);
}
