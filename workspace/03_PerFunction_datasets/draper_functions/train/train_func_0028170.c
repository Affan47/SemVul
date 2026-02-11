zoom_options_dispose (GObject *object)
{
  g_return_if_fail (object != NULL);
  g_return_if_fail (ZOOM_IS_OPTIONS (object));
  ZoomOptionsPrivate *priv = ZOOM_OPTIONS (object)->priv;

  if (priv->builder)
    {
      g_object_unref (priv->builder);
      priv->builder = NULL;
    }

  if (priv->settings)
    {
      g_object_unref (priv->settings);
      priv->settings = NULL;
    }

  g_clear_object (&priv->application_settings);

  if (priv->dialog)
    {
      gtk_widget_destroy (priv->dialog);
      priv->dialog = NULL;
    }

  G_OBJECT_CLASS (zoom_options_parent_class)->dispose (object);
}
