visu_rendering_setIcon(VisuRendering *method, const char *path)
{
  g_return_if_fail(VISU_IS_RENDERING_TYPE(method));

  if (method->priv->icon)
    {
      g_free(method->priv->icon);
      method->priv->icon = (gchar*)0;
    }
  if (!path)
    return;

  method->priv->icon = g_strdup(path);
}
