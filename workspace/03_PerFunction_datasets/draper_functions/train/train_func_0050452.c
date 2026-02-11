champlain_path_layer_remove_all (ChamplainPathLayer *layer)
{
  ChamplainPathLayerPrivate *priv = layer->priv;
  GList *elem;

  g_return_if_fail (CHAMPLAIN_IS_PATH_LAYER (layer));

  for (elem = priv->nodes; elem != NULL; elem = elem->next)
    {
      GObject *node = G_OBJECT (elem->data);

      g_signal_handlers_disconnect_by_func (node,
          G_CALLBACK (position_notify), layer);

      g_object_unref (node);
    }

  g_list_free (priv->nodes);
  priv->nodes = NULL;
  schedule_redraw (layer);
}
