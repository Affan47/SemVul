config_setting_get_format(const config_setting_t *setting)
{
  return(setting->format != 0 ? setting->format
         : setting->config->default_format);
}
