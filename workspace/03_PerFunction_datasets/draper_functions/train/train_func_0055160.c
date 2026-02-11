gst_base_video_decoder_flush_decode (GstBaseVideoDecoder * dec)
{
  GstFlowReturn res = GST_FLOW_OK;
  GList *walk;

  walk = dec->decode;

  GST_DEBUG_OBJECT (dec, "flushing buffers to decode");


  gst_base_video_decoder_flush (dec, FALSE);


  dec->process = TRUE;

  while (walk) {
    GList *next;
    GstVideoFrame *frame = (GstVideoFrame *) (walk->data);
    GstBuffer *buf = frame->sink_buffer;

    GST_DEBUG_OBJECT (dec, "decoding frame %p, ts %" GST_TIME_FORMAT,
        buf, GST_TIME_ARGS (GST_BUFFER_TIMESTAMP (buf)));

    next = g_list_next (walk);
    if (dec->current_frame)
      gst_base_video_codec_free_frame (dec->current_frame);
    dec->current_frame = frame;

    res = gst_base_video_decoder_have_frame_2 (dec);

    walk = next;
  }

  dec->process = FALSE;

  return res;
}
