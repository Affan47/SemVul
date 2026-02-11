gst_oss4_mixer_post_mixer_changed_msg (GstOss4Mixer * mixer)
{

  if (!mixer->need_update) {
    gst_mixer_mixer_changed (GST_MIXER (mixer));
    mixer->need_update = TRUE;
  }
}
