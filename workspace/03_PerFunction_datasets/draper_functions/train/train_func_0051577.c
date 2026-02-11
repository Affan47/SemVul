on_audio_tags_changed (GstElement       *pipeline,
                       gint              stream,
                       ClutterGstPlayer *player)
{
  gint current_stream;

  g_object_get (G_OBJECT (pipeline), "current-audio", &current_stream, NULL);

  if (current_stream != stream)
    return;

  g_idle_add (on_audio_changed_main_context, g_object_ref (player));
}
