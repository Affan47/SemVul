panning_completed (G_GNUC_UNUSED ChamplainKineticScrollView *scroll,
    ChamplainView *view)
{
  DEBUG_LOG ()

  ChamplainViewPrivate *priv = view->priv;
  gdouble x, y;

  if (priv->redraw_timeout != 0)
    {
      g_source_remove (priv->redraw_timeout);
      priv->redraw_timeout = 0;
    }

  champlain_viewport_get_origin (CHAMPLAIN_VIEWPORT (priv->viewport), &x, &y);

  update_coords (view, x, y, TRUE);
  load_visible_tiles (view, FALSE);
}
