adpcmenc_set_format (GstAudioEncoder * benc, GstAudioInfo * info)
{
  ADPCMEnc *enc = (ADPCMEnc *) (benc);

  enc->rate = GST_AUDIO_INFO_RATE (info);
  enc->channels = GST_AUDIO_INFO_CHANNELS (info);

  if (!adpcmenc_setup (enc))
    return FALSE;


  gst_audio_encoder_set_frame_samples_min (benc, enc->samples_per_block);
  gst_audio_encoder_set_frame_samples_max (benc, enc->samples_per_block);
  gst_audio_encoder_set_frame_max (benc, 1);

  return TRUE;
}
