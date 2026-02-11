key_file_get_int (GKeyFile *config,
                  const char *group,
                  const char *key,
                  int default_value)
{
  if (g_key_file_has_key (config, group, key, NULL))
    return g_key_file_get_integer (config, group, key, NULL);
  else
    return default_value;
}
