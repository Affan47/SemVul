on_settings_changed (GSettings    *settings,
                     const gchar  *key,
                     GtrDictPanel *panel)
{
  if (strcmp (key, DICTIONARY_SETTINGS_SOURCE_KEY) == 0)
    {
      gchar *source_name;

      source_name = g_settings_get_string (settings, key);
      gtr_dict_panel_set_source_name (panel, source_name);

      g_free (source_name);
    }
  else if (strcmp (key, DICTIONARY_SETTINGS_DATABASE_KEY) == 0)
    {
      gchar *database;

      database = g_settings_get_string (settings, key);
      gtr_dict_panel_set_database (panel, database);

      g_free (database);
    }
  else if (strcmp (key, DICTIONARY_SETTINGS_STRATEGY_KEY) == 0)
    {
      gchar *strategy;

      strategy = g_settings_get_string (settings, key);
      gtr_dict_panel_set_strategy (panel, strategy);

      g_free (strategy);
    }
}
