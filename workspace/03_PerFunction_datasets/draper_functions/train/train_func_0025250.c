gst_video_decoder_chain (GstPad * pad, GstObject * parent, GstBuffer * buf)
{
  GstVideoDecoder *decoder;
  GstFlowReturn ret = GST_FLOW_OK;

  decoder = GST_VIDEO_DECODER (parent);

  if (G_UNLIKELY (decoder->priv->do_caps)) {
    GstCaps *caps = gst_pad_get_current_caps (decoder->sinkpad);
    if (caps) {
      if (!gst_video_decoder_setcaps (decoder, caps)) {
        gst_caps_unref (caps);
        goto not_negotiated;
      }
      gst_caps_unref (caps);
    }
    decoder->priv->do_caps = FALSE;
  }

  GST_LOG_OBJECT (decoder,
      "chain PTS %" GST_TIME_FORMAT ", DTS %" GST_TIME_FORMAT " duration %"
      GST_TIME_FORMAT " size %" G_GSIZE_FORMAT,
      GST_TIME_ARGS (GST_BUFFER_PTS (buf)),
      GST_TIME_ARGS (GST_BUFFER_DTS (buf)),
      GST_TIME_ARGS (GST_BUFFER_DURATION (buf)), gst_buffer_get_size (buf));

  GST_VIDEO_DECODER_STREAM_LOCK (decoder);


  if (decoder->input_segment.format == GST_FORMAT_UNDEFINED) {
    GstEvent *event;
    GstSegment *segment = &decoder->input_segment;

    GST_WARNING_OBJECT (decoder,
        "Received buffer without a new-segment. "
        "Assuming timestamps start from 0.");

    gst_segment_init (segment, GST_FORMAT_TIME);

    event = gst_event_new_segment (segment);

    decoder->priv->current_frame_events =
        g_list_prepend (decoder->priv->current_frame_events, event);
  }

  if (decoder->input_segment.rate > 0.0)
    ret = gst_video_decoder_chain_forward (decoder, buf, FALSE);
  else
    ret = gst_video_decoder_chain_reverse (decoder, buf);

  GST_VIDEO_DECODER_STREAM_UNLOCK (decoder);
  return ret;


not_negotiated:
  {
    GST_ELEMENT_ERROR (decoder, CORE, NEGOTIATION, (NULL),
        ("decoder not initialized"));
    gst_buffer_unref (buf);
    return GST_FLOW_NOT_NEGOTIATED;
  }
}
