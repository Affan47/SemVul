champlain_view_add_layer (ChamplainView *view,
    ChamplainLayer *layer)
{
  DEBUG_LOG ()

  g_return_if_fail (CHAMPLAIN_IS_VIEW (view));
  g_return_if_fail (CHAMPLAIN_IS_LAYER (layer));

  clutter_actor_add_child (view->priv->user_layers, CLUTTER_ACTOR (layer));
  champlain_layer_set_view (layer, view);
  clutter_actor_set_child_above_sibling (view->priv->user_layers, CLUTTER_ACTOR (layer), NULL);
}
