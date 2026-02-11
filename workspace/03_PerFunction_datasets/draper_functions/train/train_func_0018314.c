gst_base_video_decoder_drop_frame (GstBaseVideoDecoder * dec,
    GstVideoFrame * frame)
{
  GstClockTime stream_time, jitter, earliest_time, qostime, timestamp;
  GstSegment *segment;
  GstMessage *qos_msg;
  gdouble proportion;

  GST_LOG_OBJECT (dec, "drop frame");

  GST_BASE_VIDEO_CODEC_STREAM_LOCK (dec);

  gst_base_video_decoder_prepare_finish_frame (dec, frame);

  GST_DEBUG_OBJECT (dec, "dropping frame %" GST_TIME_FORMAT,
      GST_TIME_ARGS (frame->presentation_timestamp));

  dec->dropped++;


  timestamp = frame->presentation_timestamp;
  proportion = GST_BASE_VIDEO_CODEC (dec)->proportion;
  segment = &GST_BASE_VIDEO_CODEC (dec)->segment;
  stream_time =
      gst_segment_to_stream_time (segment, GST_FORMAT_TIME, timestamp);
  qostime = gst_segment_to_running_time (segment, GST_FORMAT_TIME, timestamp);
  earliest_time = GST_BASE_VIDEO_CODEC (dec)->earliest_time;
  jitter = GST_CLOCK_DIFF (qostime, earliest_time);
  qos_msg = gst_message_new_qos (GST_OBJECT_CAST (dec), FALSE,
      qostime, stream_time, timestamp, GST_CLOCK_TIME_NONE);
  gst_message_set_qos_values (qos_msg, jitter, proportion, 1000000);
  gst_message_set_qos_stats (qos_msg, GST_FORMAT_BUFFERS,
      dec->processed, dec->dropped);
  gst_element_post_message (GST_ELEMENT_CAST (dec), qos_msg);


  gst_base_video_decoder_do_finish_frame (dec, frame);

  GST_BASE_VIDEO_CODEC_STREAM_UNLOCK (dec);

  return GST_FLOW_OK;
}
