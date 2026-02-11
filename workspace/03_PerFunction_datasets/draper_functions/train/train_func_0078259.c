gst_ogg_mux_clear_collectpads (GstCollectPads2 * collect)
{
  GSList *walk;

  for (walk = collect->data; walk; walk = g_slist_next (walk)) {
    GstOggPadData *oggpad = (GstOggPadData *) walk->data;
    GstBuffer *buf;

    ogg_stream_clear (&oggpad->map.stream);

    while ((buf = g_queue_pop_head (oggpad->pagebuffers)) != NULL) {
      gst_buffer_unref (buf);
    }
    g_queue_free (oggpad->pagebuffers);
    oggpad->pagebuffers = NULL;

    if (oggpad->buffer) {
      gst_buffer_unref (oggpad->buffer);
      oggpad->buffer = NULL;
    }

    if (oggpad->tags) {
      gst_tag_list_free (oggpad->tags);
      oggpad->tags = NULL;
    }

    gst_segment_init (&oggpad->segment, GST_FORMAT_TIME);
  }
}
