ges_track_text_overlay_set_font_desc (GESTrackTextOverlay * self,
    const gchar * font_desc)
{
  if (self->priv->font_desc)
    g_free (self->priv->font_desc);

  self->priv->font_desc = g_strdup (font_desc);
  GST_LOG ("setting font-desc to '%s'", font_desc);
  if (self->priv->text_el)
    g_object_set (self->priv->text_el, "font-desc", font_desc, NULL);
}
