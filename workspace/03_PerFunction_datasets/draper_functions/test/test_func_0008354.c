ar_card_theme_preimage_finalize (GObject * object)
{
  ArCardThemePreimage *theme = AR_CARD_THEME_PREIMAGE (object);

  _ar_card_theme_preimage_clear_sized_theme_data (theme);

  if (theme->cards_svg != NULL) {
    g_object_unref (theme->cards_svg);
  }
  if (theme->slot_preimage != NULL) {
    g_object_unref (theme->slot_preimage);
  }

  if (theme->font_options) {
    cairo_font_options_destroy (theme->font_options);
  }

  G_OBJECT_CLASS (ar_card_theme_preimage_parent_class)->finalize (object);
}
