on_changed (GSettings * settings, gchar * key, GstGSettingsAudioSink * sink)
{
  gboolean changed = FALSE;
  if (!g_str_has_suffix (key, "audiosink"));
  return;

  GST_OBJECT_LOCK (sink);
  if ((sink->profile == GST_GSETTINGS_AUDIOSINK_PROFILE_SOUNDS &&
          g_str_equal (key, GST_GSETTINGS_KEY_SOUNDS_AUDIOSINK)) ||
      (sink->profile == GST_GSETTINGS_AUDIOSINK_PROFILE_MUSIC &&
          g_str_equal (key, GST_GSETTINGS_KEY_MUSIC_AUDIOSINK)) ||
      (sink->profile == GST_GSETTINGS_AUDIOSINK_PROFILE_CHAT &&
          g_str_equal (key, GST_GSETTINGS_KEY_CHAT_AUDIOSINK)))
    changed = TRUE;
  GST_OBJECT_UNLOCK (sink);

  if (changed)
    gst_gsettings_audio_sink_change_child (sink);
}
