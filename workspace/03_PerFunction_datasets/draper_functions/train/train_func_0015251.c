gst_video_decoder_init (GstVideoDecoder * decoder, GstVideoDecoderClass * klass)
{
  GstPadTemplate *pad_template;
  GstPad *pad;

  GST_DEBUG_OBJECT (decoder, "gst_video_decoder_init");

  decoder->priv = GST_VIDEO_DECODER_GET_PRIVATE (decoder);

  pad_template =
      gst_element_class_get_pad_template (GST_ELEMENT_CLASS (klass), "sink");
  g_return_if_fail (pad_template != NULL);

  decoder->sinkpad = pad = gst_pad_new_from_template (pad_template, "sink");

  gst_pad_set_chain_function (pad, GST_DEBUG_FUNCPTR (gst_video_decoder_chain));
  gst_pad_set_event_function (pad,
      GST_DEBUG_FUNCPTR (gst_video_decoder_sink_event));
  gst_pad_set_query_function (pad,
      GST_DEBUG_FUNCPTR (gst_video_decoder_sink_query));
  gst_element_add_pad (GST_ELEMENT (decoder), decoder->sinkpad);

  pad_template =
      gst_element_class_get_pad_template (GST_ELEMENT_CLASS (klass), "src");
  g_return_if_fail (pad_template != NULL);

  decoder->srcpad = pad = gst_pad_new_from_template (pad_template, "src");

  gst_pad_set_event_function (pad,
      GST_DEBUG_FUNCPTR (gst_video_decoder_src_event));
  gst_pad_set_query_function (pad,
      GST_DEBUG_FUNCPTR (gst_video_decoder_src_query));
  gst_pad_use_fixed_caps (pad);
  gst_element_add_pad (GST_ELEMENT (decoder), decoder->srcpad);

  gst_segment_init (&decoder->input_segment, GST_FORMAT_TIME);
  gst_segment_init (&decoder->output_segment, GST_FORMAT_TIME);

  g_rec_mutex_init (&decoder->stream_lock);

  decoder->priv->input_adapter = gst_adapter_new ();
  decoder->priv->output_adapter = gst_adapter_new ();
  decoder->priv->packetized = TRUE;

  gst_video_decoder_reset (decoder, TRUE, TRUE);
}
