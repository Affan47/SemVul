visu_rendering_setFileTypeLabel(VisuRendering *method,
                                     guint fileType, const gchar* name)
{
  g_return_if_fail(VISU_IS_RENDERING_TYPE(method) && name && name[0]);
  g_return_if_fail(fileType < method->priv->nFiles);

  if (method->priv->fileTypeLabel[fileType])
    g_free(method->priv->fileTypeLabel[fileType]);
  method->priv->fileTypeLabel[fileType] = g_strdup(name);
}
