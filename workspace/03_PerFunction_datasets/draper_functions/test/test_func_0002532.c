meta_theme_lookup_color_constant (MetaTheme   *theme,
                                  const char  *name,
                                  char       **value)
{
  char *result;

  *value = NULL;

  if (theme->color_constants == NULL)
    return FALSE;

  result = g_hash_table_lookup (theme->color_constants, name);

  if (result)
    {
      *value = result;
      return TRUE;
    }
  else
    {
      return FALSE;
    }
}
