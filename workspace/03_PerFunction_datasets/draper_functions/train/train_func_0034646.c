gconf_string_to_double(const gchar* str,
                       gdouble*     retloc)
{
  char *end;

  errno = 0;
  *retloc = g_ascii_strtod (str, &end);
  if (end == str || errno != 0)
    {
      *retloc = 0.0;
      return FALSE;
    }
  else
    return TRUE;
}
