gst_vp8_dec_set_format (GstVideoDecoder * decoder, GstVideoCodecState * state)
{
  GstVP8Dec *gst_vp8_dec = GST_VP8_DEC (decoder);

  GST_DEBUG_OBJECT (gst_vp8_dec, "set_format");

  if (gst_vp8_dec->decoder_inited)
    vpx_codec_destroy (&gst_vp8_dec->decoder);
  gst_vp8_dec->decoder_inited = FALSE;

  if (gst_vp8_dec->input_state)
    gst_video_codec_state_unref (gst_vp8_dec->input_state);
  gst_vp8_dec->input_state = gst_video_codec_state_ref (state);

  return TRUE;
}
