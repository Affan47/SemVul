format_reltime (gint seconds)
{
  gint magnitude;
  const gchar *ending;
  gchar *ret;

  if (seconds >= 0)
    {
      magnitude = seconds;
      ending = "from now";
    }
  else
    {
      magnitude = -seconds;
      ending = "ago";
    }

  if (magnitude >= 60)
    {
      ret = g_strdup_printf ("%d min %d sec %s", magnitude/60, magnitude%60, ending);
    }
  else
    {
      ret = g_strdup_printf ("%d sec %s", magnitude, ending);
    }

  return ret;
}
