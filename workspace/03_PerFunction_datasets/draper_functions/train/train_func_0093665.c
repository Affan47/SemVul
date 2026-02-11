GNUNET_PLUGIN_test (const char *library_name)
{
  void *libhandle;
  GNUNET_PLUGIN_Callback init;
  struct PluginList plug;

  if (!initialized)
  {
    initialized = GNUNET_YES;
    plugin_init ();
  }
  libhandle = lt_dlopenext (library_name);
  if (libhandle == NULL)
    return GNUNET_NO;
  plug.handle = libhandle;
  plug.name = (char *) library_name;
  init = resolve_function (&plug, "init");
  if (init == NULL)
  {
    GNUNET_break (0);
    lt_dlclose (libhandle);
    return GNUNET_NO;
  }
  lt_dlclose (libhandle);
  return GNUNET_YES;
}
