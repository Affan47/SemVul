gtk_shruler_set_position (GtkSHRuler *ruler,
                         gdouble    position)
{
  GtkSHRulerPrivate *priv;

  g_return_if_fail (GTK_IS_SHRULER (ruler));

  priv = GTK_SHRULER_GET_PRIVATE (ruler);

  if (priv->position != position)
    {
      priv->position = position;
      g_object_notify (G_OBJECT (ruler), "position");
    }
}
