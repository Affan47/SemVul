ar_card_themes_get_theme_by_name (ArCardThemes *theme_manager,
                                     const char *theme_name)
{
  GType type;
  char *filename;
  ArCardThemeInfo *theme_info = NULL;

  g_return_val_if_fail (AR_IS_CARD_THEMES (theme_manager), NULL);

  filename = theme_filename_and_type_from_name (theme_name, &type);
  ar_debug_print (AR_DEBUG_CARD_THEME,
                      "Resolved card type=%s filename=%s\n",
                      g_type_name (type),
                      filename);

  if (filename == NULL || type == G_TYPE_INVALID)
    return NULL;


  {
    ThemesByTypeAndFilenameData data = { type, filename, NULL };

    g_hash_table_foreach (theme_manager->theme_infos, (GHFunc) themes_foreach_by_type_and_filename, &data);

    theme_info = data.theme_info;
  }

  if (theme_info == NULL &&
      !theme_manager->theme_infos_loaded) {
    LookupData data = { filename, NULL };

    ar_card_themes_foreach_theme_dir (type, (ArCardThemeForeachFunc) ar_card_themes_try_theme_info_by_filename, &data);
    theme_info = data.theme_info;

    if (theme_info)
      g_hash_table_replace (theme_manager->theme_infos, theme_info->pref_name, theme_info);
  }

  g_free (filename);

  if (theme_info == NULL)
    return NULL;

  return ar_card_themes_get_theme (theme_manager, theme_info);
}
