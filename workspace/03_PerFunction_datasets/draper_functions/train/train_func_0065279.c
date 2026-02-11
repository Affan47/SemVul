gnm_font_button_get_preview_text (GnmFontButton *font_button)
{
  GnmFontButtonPrivate *priv = font_button->priv;

  if (priv->font_dialog)
    return gtk_font_chooser_get_preview_text (GTK_FONT_CHOOSER (priv->font_dialog));

  return g_strdup (priv->preview_text);
}
