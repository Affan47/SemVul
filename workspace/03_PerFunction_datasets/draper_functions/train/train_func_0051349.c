add_node (ChamplainPathLayer *layer,
    ChamplainLocation *location,
    gboolean prepend,
    guint position)
{
  ChamplainPathLayerPrivate *priv = layer->priv;

  g_signal_connect (G_OBJECT (location), "notify::latitude",
      G_CALLBACK (position_notify), layer);

  g_object_ref_sink (location);

  if (prepend)
    priv->nodes = g_list_prepend (priv->nodes, location);
  else
    priv->nodes = g_list_insert (priv->nodes, location, position);
  schedule_redraw (layer);
}
