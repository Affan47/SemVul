theora_dec_stop (GstVideoDecoder * decoder)
{
  GstTheoraDec *dec = GST_THEORA_DEC (decoder);

  GST_DEBUG_OBJECT (dec, "stop");

  th_info_clear (&dec->info);
  th_comment_clear (&dec->comment);
  if (dec->setup) {
    th_setup_free (dec->setup);
    dec->setup = NULL;
  }
  if (dec->decoder) {
    th_decode_free (dec->decoder);
    dec->decoder = NULL;
  }

  if (dec->input_state) {
    gst_video_codec_state_unref (dec->input_state);
    dec->input_state = NULL;
  }
  if (dec->output_state) {
    gst_video_codec_state_unref (dec->output_state);
    dec->output_state = NULL;
  }
  dec->can_crop = FALSE;

  return TRUE;
}
