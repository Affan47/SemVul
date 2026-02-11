gnm_font_button_label_use_font (GnmFontButton *font_button)
{
  PangoFontDescription *desc;

  if (font_button->priv->use_font)
    {
      desc = pango_font_description_copy (font_button->priv->font_desc);

      if (!font_button->priv->use_size)
        pango_font_description_unset_fields (desc, PANGO_FONT_MASK_SIZE);
    }
  else
    desc = NULL;

  gtk_widget_override_font (font_button->priv->font_label, desc);

  if (desc)
    pango_font_description_free (desc);
}
