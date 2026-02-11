clutter_gst_player_deinit (ClutterGstPlayer *player)
{
  ClutterGstPlayerPrivate *priv;

  g_return_if_fail (CLUTTER_GST_IS_PLAYER (player));

  priv = PLAYER_GET_PRIVATE (player);

  if (priv == NULL)
    return;

  PLAYER_SET_PRIVATE (player, NULL);

  if (priv->tick_timeout_id)
    {
      g_source_remove (priv->tick_timeout_id);
      priv->tick_timeout_id = 0;
    }

  if (priv->buffering_timeout_id)
    {
      g_source_remove (priv->buffering_timeout_id);
      priv->buffering_timeout_id = 0;
    }

  if (priv->download_buffering_element)
    {
      g_object_unref (priv->download_buffering_element);
      priv->download_buffering_element = NULL;
    }

  gst_element_set_state (priv->pipeline, GST_STATE_NULL);

  if (priv->bus)
    {
      gst_bus_remove_signal_watch (priv->bus);
      priv->bus = NULL;
    }

  if (priv->pipeline)
    {
      gst_object_unref (GST_OBJECT (priv->pipeline));
      priv->pipeline = NULL;
    }

  g_free (priv->uri);
  g_free (priv->font_name);
  g_free (priv->user_agent);
  free_tags_list (&priv->audio_streams);
  free_tags_list (&priv->subtitle_tracks);

  g_slice_free (ClutterGstPlayerPrivate, priv);
}
