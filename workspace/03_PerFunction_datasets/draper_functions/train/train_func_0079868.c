validate_name (const gchar * name)
{
  guint i, len;

  len = strlen (name);
  if (len == 0)
    return FALSE;


  if (!g_ascii_isalpha (name[0]) || !g_ascii_islower (name[0]))
    return FALSE;


  for (i = 1; i < len; i++) {

    if (g_ascii_isupper (name[i]))
      return FALSE;

    if (g_ascii_isdigit (name[i]))
      continue;

    if (name[i] == '-')
      continue;

    if (!g_ascii_isalpha (name[i]))
      return FALSE;
  }

  return TRUE;
}
