build_strings_for_face (SushiFontWidget *self)
{


  if (check_font_contain_text (self->priv->face, lowercase_text_stock))
    self->priv->lowercase_text = lowercase_text_stock;
  else
    self->priv->lowercase_text = NULL;

  if (check_font_contain_text (self->priv->face, uppercase_text_stock))
    self->priv->uppercase_text = uppercase_text_stock;
  else
    self->priv->uppercase_text = NULL;

  if (check_font_contain_text (self->priv->face, punctuation_text_stock))
    self->priv->punctuation_text = punctuation_text_stock;
  else
    self->priv->punctuation_text = NULL;

  if (!set_pango_sample_string (self))
    self->priv->sample_string = random_string_from_available_chars (self->priv->face, 36);

  g_free (self->priv->font_name);
  self->priv->font_name = NULL;

  if (self->priv->face->family_name != NULL) {
    gchar *font_name =
      g_strconcat (self->priv->face->family_name, " ",
                   self->priv->face->style_name, NULL);

    if (check_font_contain_text (self->priv->face, font_name))
      self->priv->font_name = font_name;
    else
      g_free (font_name);
  }
}
