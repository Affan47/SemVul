get_drag_threshold (ClutterDragAction *action,
                    gint              *x_threshold,
                    gint              *y_threshold)
{
  ClutterDragActionPrivate *priv = action->priv;
  ClutterSettings *settings = clutter_settings_get_default ();
  gint x_res, y_res, default_threshold;

  g_object_get (settings, "dnd-drag-threshold", &default_threshold, NULL);

  if (priv->x_drag_threshold < 0)
    x_res = default_threshold;
  else
    x_res = priv->x_drag_threshold;

  if (priv->y_drag_threshold < 0)
    y_res = default_threshold;
  else
    y_res = priv->y_drag_threshold;

  if (x_threshold != NULL)
    *x_threshold = x_res;

  if (y_threshold != NULL)
    *y_threshold = y_res;
}
