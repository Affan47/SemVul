duration_to_seconds (const gchar *str)
{
  gint seconds = 0;
  gchar **parts;
  gint i;
  guint multiplier = 1;

  if (!str || str[0] == '\0') {
    return 0;
  }

  parts = g_strsplit (str, ":", 3);


  i = 0;
  while (parts[i]) i++;
  if (i == 0) {
    g_strfreev (parts);
    return 0;
  } else {
    i--;
  }

  do {
    seconds += atoi (parts[i]) * multiplier;
    multiplier *= 60;
    i--;
  } while (i >= 0);

  g_strfreev (parts);

  return seconds;
}
