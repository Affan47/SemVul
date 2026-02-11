clutter_alpha_easing_func (ClutterAlpha *alpha,
                           gpointer      data G_GNUC_UNUSED)
{
  ClutterAlphaPrivate *priv = alpha->priv;
  ClutterTimeline *timeline = priv->timeline;
  gdouble t, d;

  if (G_UNLIKELY (priv->timeline == NULL))
    return 0.0;

  t = clutter_timeline_get_elapsed_time (timeline);
  d = clutter_timeline_get_duration (timeline);

  return clutter_easing_for_mode (priv->mode, t, d);
}
