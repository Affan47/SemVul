_update_idle_cb (ChamplainView *view)
{
  DEBUG_LOG ()

  ChamplainViewPrivate *priv = view->priv;

  if (!priv->kinetic_scroll)
    return FALSE;

  clutter_actor_set_size (priv->kinetic_scroll,
      priv->viewport_width,
      priv->viewport_height);

  resize_viewport (view);

  if (priv->keep_center_on_resize)
    champlain_view_center_on (view, priv->latitude, priv->longitude);
  else
    load_visible_tiles (view, FALSE);

  return FALSE;
}
