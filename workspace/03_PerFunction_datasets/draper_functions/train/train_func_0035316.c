clutter_rectangle_set_color (ClutterRectangle   *rectangle,
			     const ClutterColor *color)
{
  ClutterRectanglePrivate *priv;

  g_return_if_fail (CLUTTER_IS_RECTANGLE (rectangle));
  g_return_if_fail (color != NULL);

  g_object_ref (rectangle);

  priv = rectangle->priv;

  priv->color.red = color->red;
  priv->color.green = color->green;
  priv->color.blue = color->blue;
  priv->color.alpha = color->alpha;

#if 0

  if (clutter_color_equal (&priv->color, &priv->border_color))
    priv->has_border = FALSE;
  else
    priv->has_border = TRUE;
#endif

  clutter_actor_queue_redraw (CLUTTER_ACTOR (rectangle));

  g_object_notify (G_OBJECT (rectangle), "color");
  g_object_notify (G_OBJECT (rectangle), "has-border");
  g_object_unref (rectangle);
}
