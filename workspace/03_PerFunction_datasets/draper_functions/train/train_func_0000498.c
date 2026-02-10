champlain_network_tile_source_dispose (GObject *object)
{
  ChamplainNetworkTileSourcePrivate *priv = CHAMPLAIN_NETWORK_TILE_SOURCE (object)->priv;

  if (priv->soup_session)
    {
      soup_session_abort (priv->soup_session);
      g_object_unref (priv->soup_session);
      priv->soup_session = NULL;
    }

  G_OBJECT_CLASS (champlain_network_tile_source_parent_class)->dispose (object);
}
