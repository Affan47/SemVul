frogr_config_get_instance (void)
{
  if (_instance)
    return _instance;

  return FROGR_CONFIG (g_object_new (FROGR_TYPE_CONFIG, NULL));
}
