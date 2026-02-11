tre_version(void)
{
  static char str[256];
  char *version;

  if (str[0] == 0)
    {
      tre_config(TRE_CONFIG_VERSION, &version);
      sprintf(str, "TRE %s (LGPL)", version);
    }
  return str;
}
