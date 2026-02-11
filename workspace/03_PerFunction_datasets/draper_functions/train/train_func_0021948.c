set_playing (ClutterGstPlayer *player,
             gboolean          playing)
{
  ClutterGstPlayerPrivate *priv = PLAYER_GET_PRIVATE (player);

  if (!priv->pipeline)
    return;

  CLUTTER_GST_NOTE (MEDIA, "set playing: %d", playing);

  priv->in_error = FALSE;
  priv->in_eos = FALSE;

  priv->target_state = playing ? GST_STATE_PLAYING : GST_STATE_PAUSED;

  if (priv->uri)
    {
      set_in_seek (player, FALSE);

      gst_element_set_state (priv->pipeline, priv->target_state);
    }
  else
    {
      if (playing)
       g_warning ("Unable to start playing: no URI is set");
    }

  g_object_notify (G_OBJECT (player), "playing");
  g_object_notify (G_OBJECT (player), "progress");
}
