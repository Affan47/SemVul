gst_vp9_dec_flush (GstVideoDecoder * base_video_decoder)
{
  GstVP9Dec *decoder;

  GST_DEBUG_OBJECT (base_video_decoder, "flush");

  decoder = GST_VP9_DEC (base_video_decoder);

  if (decoder->output_state) {
    gst_video_codec_state_unref (decoder->output_state);
    decoder->output_state = NULL;
  }

  if (decoder->decoder_inited)
    vpx_codec_destroy (&decoder->decoder);
  decoder->decoder_inited = FALSE;

  return TRUE;
}
