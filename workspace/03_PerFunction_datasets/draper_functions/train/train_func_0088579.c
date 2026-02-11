gucharmap_chartable_finalize (GObject *object)
{
  GucharmapChartable *chartable = GUCHARMAP_CHARTABLE (object);
  GucharmapChartablePrivate *priv = chartable->priv;

  if (priv->font_desc)
    pango_font_description_free (priv->font_desc);

  gucharmap_chartable_clear_pango_layout (chartable);

  gtk_target_list_unref (priv->target_list);

  if (priv->codepoint_list)
    g_object_unref (priv->codepoint_list);

  destroy_zoom_window (chartable);

  G_OBJECT_CLASS (gucharmap_chartable_parent_class)->finalize (object);
}
