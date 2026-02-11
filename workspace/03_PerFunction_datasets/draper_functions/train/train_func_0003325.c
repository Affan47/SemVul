bacon_video_widget_set_audio_output_type (BaconVideoWidget *bvw,
                                          BvwAudioOutputType type)
{
  g_return_if_fail (BACON_IS_VIDEO_WIDGET (bvw));

  if (type == bvw->priv->speakersetup)
    return;
  else if (type == BVW_AUDIO_SOUND_AC3PASSTHRU)
    return;

  bvw->priv->speakersetup = type;
  g_object_notify (G_OBJECT (bvw), "audio-output-type");

  set_audio_filter (bvw);
}
