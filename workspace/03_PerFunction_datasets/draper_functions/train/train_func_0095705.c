champlain_view_realized_cb (ChamplainView *view,
    G_GNUC_UNUSED GParamSpec *pspec)
{
  DEBUG_LOG ()

  ChamplainViewPrivate *priv = view->priv;

  if (!CLUTTER_ACTOR_IS_REALIZED (view))
    return;

  clutter_actor_grab_key_focus (priv->kinetic_scroll);

  resize_viewport (view);
  champlain_view_center_on (view, priv->latitude, priv->longitude);

  g_object_notify (G_OBJECT (view), "zoom-level");
  g_object_notify (G_OBJECT (view), "map-source");
  g_signal_emit_by_name (view, "layer-relocated", NULL);
}
