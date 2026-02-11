gst_ogg_pad_dispose (GObject * object)
{
  GstOggPad *pad = GST_OGG_PAD (object);

  pad->chain = NULL;
  pad->ogg = NULL;

  g_list_foreach (pad->map.headers, (GFunc) _ogg_packet_free, NULL);
  g_list_free (pad->map.headers);
  pad->map.headers = NULL;
  g_list_foreach (pad->map.queued, (GFunc) _ogg_packet_free, NULL);
  g_list_free (pad->map.queued);
  pad->map.queued = NULL;

  g_free (pad->map.index);
  pad->map.index = NULL;


  g_list_foreach (pad->continued, (GFunc) gst_ogg_page_free, NULL);
  g_list_free (pad->continued);
  pad->continued = NULL;

  if (pad->map.caps) {
    gst_caps_unref (pad->map.caps);
    pad->map.caps = NULL;
  }

  if (pad->map.taglist) {
    gst_tag_list_unref (pad->map.taglist);
    pad->map.taglist = NULL;
  }

  ogg_stream_reset (&pad->map.stream);

  G_OBJECT_CLASS (gst_ogg_pad_parent_class)->dispose (object);
}
