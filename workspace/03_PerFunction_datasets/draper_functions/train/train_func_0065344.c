_ar_card_theme_class_foreach_env (ArCardThemeClass *klass,
                                     const char *env,
                                     ArCardThemeForeachFunc callback,
                                     gpointer data)
{
  const char *value;
  char **paths;
  guint i;
  gboolean retval = TRUE;

  value = g_getenv (env);
  if (!value || !value[0])
    return TRUE;

  paths = g_strsplit (value, G_SEARCHPATH_SEPARATOR_S, -1);
  if (!paths)
    return TRUE;

  for (i = 0; paths[i]; ++i) {
    const char *path = paths[i];

    if (!paths[0])
      continue;

    retval = callback (klass, path, data);
    if (!retval)
      break;
  }

  g_strfreev (paths);

  return retval;
}
