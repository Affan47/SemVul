lookup(const char *path) const
  throw(SettingNotFoundException)
{
  config_setting_t *s = config_lookup(_config, path);
  if(! s)
    throw SettingNotFoundException(path);

  return(Setting::wrapSetting(s));
}
