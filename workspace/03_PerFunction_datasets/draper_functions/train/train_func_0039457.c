theora_enc_set_format (GstVideoEncoder * benc, GstVideoCodecState * state)
{
  GstTheoraEnc *enc = GST_THEORA_ENC (benc);
  GstVideoInfo *info = &state->info;

  enc->width = GST_VIDEO_INFO_WIDTH (info);
  enc->height = GST_VIDEO_INFO_HEIGHT (info);

  th_info_clear (&enc->info);
  th_info_init (&enc->info);


  enc->info.frame_width = GST_ROUND_UP_16 (enc->width);
  enc->info.frame_height = GST_ROUND_UP_16 (enc->height);
  enc->info.pic_width = enc->width;
  enc->info.pic_height = enc->height;
  switch (GST_VIDEO_INFO_FORMAT (info)) {
    case GST_VIDEO_FORMAT_I420:
      enc->info.pixel_fmt = TH_PF_420;
      break;
    case GST_VIDEO_FORMAT_Y42B:
      enc->info.pixel_fmt = TH_PF_422;
      break;
    case GST_VIDEO_FORMAT_Y444:
      enc->info.pixel_fmt = TH_PF_444;
      break;
    default:
      g_assert_not_reached ();
  }

  enc->info.fps_numerator = enc->fps_n = GST_VIDEO_INFO_FPS_N (info);
  enc->info.fps_denominator = enc->fps_d = GST_VIDEO_INFO_FPS_D (info);
  enc->info.aspect_numerator = GST_VIDEO_INFO_PAR_N (info);
  enc->info.aspect_denominator = GST_VIDEO_INFO_PAR_D (info);

  enc->info.colorspace = TH_CS_UNSPECIFIED;


  if (enc->input_state)
    gst_video_codec_state_unref (enc->input_state);
  enc->input_state = gst_video_codec_state_ref (state);


  enc->info.keyframe_granule_shift = _ilog (enc->keyframe_force - 1);
  GST_DEBUG_OBJECT (enc,
      "keyframe_frequency_force is %d, granule shift is %d",
      enc->keyframe_force, enc->info.keyframe_granule_shift);

  theora_enc_flush (benc);
  enc->initialised = TRUE;

  return TRUE;
}
