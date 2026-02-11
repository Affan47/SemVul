pre_parse_hook (GOptionContext  *context,
                GOptionGroup    *group,
                gpointer         data,
                GError         **error)
{
  const char *env_string;

  if (gdict_is_initialized)
    return TRUE;

#ifdef GDICT_ENABLE_DEBUG
  env_string = g_getenv ("GDICT_DEBUG");
  if (env_string != NULL)
    {
      gdict_debug_flags =
        g_parse_debug_string (env_string,
                              gdict_debug_keys,
                              G_N_ELEMENTS (gdict_debug_keys));
    }
#else
  env_string = NULL;
#endif

  return TRUE;
}
