get_playing (ClutterGstPlayer *player)
{
  ClutterGstPlayerPrivate *priv = PLAYER_GET_PRIVATE (player);
  GstState state, pending;
  gboolean playing;

  if (!priv->pipeline)
    return FALSE;

  gst_element_get_state (priv->pipeline, &state, &pending, 0);

  if (pending)
    playing = (pending == GST_STATE_PLAYING);
  else
    playing = (state == GST_STATE_PLAYING);

  CLUTTER_GST_NOTE (MEDIA, "get playing: %d", playing);

  return playing;
}
