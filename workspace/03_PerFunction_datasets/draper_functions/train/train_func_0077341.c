view_size_changed_cb (ChamplainView *view,
    G_GNUC_UNUSED GParamSpec *pspec)
{
  ChamplainViewPrivate *priv = GET_PRIVATE (view);
  gint width, height;

  width = clutter_actor_get_width (CLUTTER_ACTOR (view));
  height = clutter_actor_get_height (CLUTTER_ACTOR (view));

  if (priv->viewport_width != width || priv->viewport_height != height)
    {
      g_idle_add_full (CLUTTER_PRIORITY_REDRAW,
          (GSourceFunc) _update_idle_cb,
          g_object_ref (view),
          (GDestroyNotify) g_object_unref);
    }

  priv->viewport_width = width;
  priv->viewport_height = height;
}
