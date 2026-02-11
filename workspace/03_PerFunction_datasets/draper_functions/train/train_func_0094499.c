ar_card_themes_request_themes (ArCardThemes *theme_manager)
{
  g_return_if_fail (AR_IS_CARD_THEMES (theme_manager));

  if (theme_manager->theme_infos_loaded)
    return;

  ar_card_themes_load_theme_infos (theme_manager);
}
