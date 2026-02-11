ar_card_theme_preimage_set_font_options (ArCardTheme *card_theme,
                                            const cairo_font_options_t *font_options)
{
  ArCardThemePreimage *theme = (ArCardThemePreimage *) card_theme;

  if (font_options &&
      theme->font_options &&
      cairo_font_options_equal (font_options, theme->font_options))
    return;

  if (theme->font_options) {
    cairo_font_options_destroy (theme->font_options);
  }

  if (font_options) {
    theme->font_options = cairo_font_options_copy (font_options);
  } else {
    theme->font_options = NULL;
  }

  _ar_card_theme_preimage_clear_sized_theme_data (theme);
  _ar_card_theme_emit_changed (card_theme);
}
