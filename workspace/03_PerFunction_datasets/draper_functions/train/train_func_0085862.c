gst_schro_dec_handle_frame (GstBaseVideoDecoder * base_video_decoder,
    GstVideoFrame * frame)
{
  GstSchroDec *schro_dec;
  SchroBuffer *input_buffer;

  schro_dec = GST_SCHRO_DEC (base_video_decoder);

  GST_DEBUG ("handle frame");

  input_buffer = gst_schro_wrap_gst_buffer (frame->sink_buffer);
  frame->sink_buffer = NULL;

  input_buffer->tag = schro_tag_new (frame, NULL);

  schro_decoder_autoparse_push (schro_dec->decoder, input_buffer);

  return gst_schro_dec_process (schro_dec, FALSE);
}
