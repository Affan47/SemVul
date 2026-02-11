find_unloaded_locale (const char *locale,
                      gpointer    value,
                      gboolean   *any_unloaded)
{
  if (value != NULL)
    return FALSE;

  *any_unloaded = TRUE;

  return TRUE;
}
