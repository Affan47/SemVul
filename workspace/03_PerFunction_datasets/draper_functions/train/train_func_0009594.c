gst_base_video_decoder_push_src_event (GstBaseVideoDecoder * decoder,
    GstEvent * event)
{


  if (!GST_EVENT_IS_SERIALIZED (event)
      || GST_EVENT_TYPE (event) == GST_EVENT_EOS
      || GST_EVENT_TYPE (event) == GST_EVENT_FLUSH_STOP)
    return gst_pad_push_event (decoder->base_video_codec.srcpad, event);

  GST_BASE_VIDEO_CODEC_STREAM_LOCK (decoder);
  decoder->current_frame_events =
      g_list_prepend (decoder->current_frame_events, event);
  GST_BASE_VIDEO_CODEC_STREAM_UNLOCK (decoder);

  return TRUE;
}
