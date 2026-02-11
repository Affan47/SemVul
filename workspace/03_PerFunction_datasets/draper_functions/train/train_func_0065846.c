ges_text_overlay_set_text (GESTextOverlay * self, const gchar * text)
{
  GST_DEBUG ("self:%p, text:%s", self, text);

  if (self->priv->text)
    g_free (self->priv->text);

  self->priv->text = g_strdup (text);
  if (self->priv->text_el)
    g_object_set (self->priv->text_el, "text", text, NULL);
}
