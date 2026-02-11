gst_icydemux_reset (GstICYDemux * icydemux)
{


  icydemux->meta_interval = -1;
  icydemux->remaining = 0;

  icydemux->typefinding = TRUE;

  gst_caps_replace (&(icydemux->src_caps), NULL);

  gst_icydemux_remove_srcpad (icydemux);

  if (icydemux->cached_tags) {
    gst_tag_list_free (icydemux->cached_tags);
    icydemux->cached_tags = NULL;
  }

  if (icydemux->cached_events) {
    g_list_foreach (icydemux->cached_events,
        (GFunc) gst_mini_object_unref, NULL);
    g_list_free (icydemux->cached_events);
    icydemux->cached_events = NULL;
  }

  if (icydemux->meta_adapter) {
    gst_adapter_clear (icydemux->meta_adapter);
    g_object_unref (icydemux->meta_adapter);
    icydemux->meta_adapter = NULL;
  }

  if (icydemux->typefind_buf) {
    gst_buffer_unref (icydemux->typefind_buf);
    icydemux->typefind_buf = NULL;
  }

  if (icydemux->content_type) {
    g_free (icydemux->content_type);
    icydemux->content_type = NULL;
  }
}
