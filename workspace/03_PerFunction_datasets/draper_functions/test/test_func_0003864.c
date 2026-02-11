gst_rmdemux_reset (GstRMDemux * rmdemux)
{
  GSList *cur;

  GST_OBJECT_LOCK (rmdemux);
  rmdemux->running = FALSE;
  GST_OBJECT_UNLOCK (rmdemux);

  for (cur = rmdemux->streams; cur; cur = cur->next) {
    GstRMDemuxStream *stream = cur->data;

    g_object_unref (stream->adapter);
    gst_rmdemux_stream_clear_cached_subpackets (rmdemux, stream);
    gst_element_remove_pad (GST_ELEMENT (rmdemux), stream->pad);
    if (stream->pending_tags)
      gst_tag_list_free (stream->pending_tags);
    if (stream->subpackets)
      g_ptr_array_free (stream->subpackets, TRUE);
    g_free (stream->index);
    g_free (stream);
  }
  g_slist_free (rmdemux->streams);
  rmdemux->streams = NULL;
  rmdemux->n_audio_streams = 0;
  rmdemux->n_video_streams = 0;

  if (rmdemux->pending_tags != NULL) {
    gst_tag_list_free (rmdemux->pending_tags);
    rmdemux->pending_tags = NULL;
  }

  gst_adapter_clear (rmdemux->adapter);
  rmdemux->state = RMDEMUX_STATE_HEADER;
  rmdemux->have_pads = FALSE;

  gst_segment_init (&rmdemux->segment, GST_FORMAT_UNDEFINED);
  rmdemux->first_ts = GST_CLOCK_TIME_NONE;
  rmdemux->base_ts = GST_CLOCK_TIME_NONE;
  rmdemux->need_newsegment = TRUE;
}
