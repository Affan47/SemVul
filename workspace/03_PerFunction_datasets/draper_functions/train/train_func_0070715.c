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

  mix->sinkpads = g_slist_remove (mix->sinkpads, pad);
  gst_child_proxy_child_removed (GST_OBJECT (mix), GST_OBJECT (mixpad));
  mix->numpads--;

  update_caps = mix->format != GST_VIDEO_FORMAT_UNKNOWN;
  GST_VIDEO_MIXER2_UNLOCK (mix);

  gst_collect_pads2_remove_pad (mix->collect, pad);

  if (update_caps)
    gst_videomixer2_update_src_caps (mix);

  gst_element_remove_pad (element, pad);
  return;
error:
  GST_VIDEO_MIXER2_UNLOCK (mix);
}
