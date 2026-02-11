viewport_pos_changed_cb (G_GNUC_UNUSED GObject *gobject,
    G_GNUC_UNUSED GParamSpec *arg1,
    ChamplainView *view)
{
  DEBUG_LOG ()

  ChamplainViewPrivate *priv = view->priv;
  gdouble x, y;

  if (priv->redraw_timeout == 0)
    priv->redraw_timeout = g_timeout_add (350, redraw_timeout_cb, view);

  champlain_viewport_get_origin (CHAMPLAIN_VIEWPORT (priv->viewport), &x, &y);

  if (ABS (x - priv->viewport_x) > 100 || ABS (y - priv->viewport_y) > 100)
    {
      update_coords (view, x, y, FALSE);
      load_visible_tiles (view, FALSE);
      priv->location_updated = TRUE;
    }
}
