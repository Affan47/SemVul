xsettings_manager_set_setting (XSettingsManager *manager,
                               const gchar      *name,
                               gint              tier,
                               GVariant         *value)
{
  XSettingsSetting *setting;

  setting = g_hash_table_lookup (manager->settings, name);

  if (setting == NULL)
    {
      setting = xsettings_setting_new (name);
      setting->last_change_serial = manager->serial;
      g_hash_table_insert (manager->settings, setting->name, setting);
    }

  xsettings_setting_set (setting, tier, value, manager->serial);

  if (xsettings_setting_get (setting) == NULL)
    g_hash_table_remove (manager->settings, name);
}
