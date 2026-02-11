gst_sdp_demux_stream_push_event (GstSDPDemux * demux, GstSDPStream * stream,
    GstEvent * event)
{

  if (stream->srcpad == NULL)
    goto done;

  if (stream->channelpad[0]) {
    gst_event_ref (event);
    gst_pad_send_event (stream->channelpad[0], event);
  }

  if (stream->channelpad[1]) {
    gst_event_ref (event);
    gst_pad_send_event (stream->channelpad[1], event);
  }

done:
  gst_event_unref (event);
}
