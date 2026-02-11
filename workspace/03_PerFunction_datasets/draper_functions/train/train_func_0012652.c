gst_dash_demux_setup_all_streams (GstDashDemux * demux)
{
  guint i;
  GSList *streams = NULL;

  GST_MPD_CLIENT_LOCK (demux->client);

  gst_active_streams_free (demux->client);

  if (!gst_dash_demux_setup_mpdparser_streams (demux, demux->client)) {
    return FALSE;
  }

  GST_DEBUG_OBJECT (demux, "Creating stream objects");
  for (i = 0; i < gst_mpdparser_get_nb_active_stream (demux->client); i++) {
    GstDashDemuxStream *stream;
    GstActiveStream *active_stream;
    GstCaps *caps;
    GstEvent *event;
    gchar *stream_id;

    active_stream = gst_mpdparser_get_active_stream_by_index (demux->client, i);
    if (active_stream == NULL)
      continue;

    stream = g_new0 (GstDashDemuxStream, 1);
    caps = gst_dash_demux_get_input_caps (demux, active_stream);
    stream->queue =
        gst_data_queue_new ((GstDataQueueCheckFullFunction) _check_queue_full,
        NULL, NULL, demux);

    stream->index = i;
    stream->input_caps = caps;
    stream->need_header = TRUE;
    stream->has_data_queued = FALSE;
    gst_download_rate_init (&stream->dnl_rate);
    gst_download_rate_set_max_length (&stream->dnl_rate,
        DOWNLOAD_RATE_HISTORY_MAX);

    GST_LOG_OBJECT (demux, "Creating stream %d %" GST_PTR_FORMAT, i, caps);
    streams = g_slist_prepend (streams, stream);
    stream->pad = gst_dash_demux_create_pad (demux);

    stream_id =
        gst_pad_create_stream_id_printf (stream->pad,
        GST_ELEMENT_CAST (demux), "%d", i);

    event =
        gst_pad_get_sticky_event (demux->sinkpad, GST_EVENT_STREAM_START, 0);
    if (event) {
      if (gst_event_parse_group_id (event, &demux->group_id))
        demux->have_group_id = TRUE;
      else
        demux->have_group_id = FALSE;
      gst_event_unref (event);
    } else if (!demux->have_group_id) {
      demux->have_group_id = TRUE;
      demux->group_id = gst_util_group_id_next ();
    }
    event = gst_event_new_stream_start (stream_id);
    if (demux->have_group_id)
      gst_event_set_group_id (event, demux->group_id);

    gst_pad_push_event (stream->pad, event);
    g_free (stream_id);

    gst_dash_demux_stream_push_event (stream, gst_event_new_caps (caps));
  }
  streams = g_slist_reverse (streams);

  demux->next_periods = g_slist_append (demux->next_periods, streams);
  GST_MPD_CLIENT_UNLOCK (demux->client);

  return TRUE;
}
