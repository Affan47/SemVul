player_configure_buffering_timeout (ClutterGstPlayer *player,
                                    guint             ms)
{
  ClutterGstPlayerPrivate *priv = PLAYER_GET_PRIVATE (player);

  if (priv->buffering_timeout_id)
    {
      g_source_remove (priv->buffering_timeout_id);
      priv->buffering_timeout_id = 0;
    }

  if (ms)
    {
      priv->buffering_timeout_id =
        g_timeout_add (ms, player_buffering_timeout, player);
    }
}
