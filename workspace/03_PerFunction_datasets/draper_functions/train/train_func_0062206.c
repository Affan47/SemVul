empathy_duration_to_string (guint seconds)
{
  if (seconds < 60)
    {
      return g_strdup_printf (ngettext ("%d second ago",
        "%d seconds ago", seconds), seconds);
    }
  else if (seconds < (60 * 60))
    {
      seconds /= 60;
      return g_strdup_printf (ngettext ("%d minute ago",
        "%d minutes ago", seconds), seconds);
    }
  else if (seconds < (60 * 60 * 24))
    {
      seconds /= 60 * 60;
      return g_strdup_printf (ngettext ("%d hour ago",
        "%d hours ago", seconds), seconds);
    }
  else if (seconds < (60 * 60 * 24 * 7))
    {
      seconds /= 60 * 60 * 24;
      return g_strdup_printf (ngettext ("%d day ago",
        "%d days ago", seconds), seconds);
    }
  else if (seconds < (60 * 60 * 24 * 30))
    {
      seconds /= 60 * 60 * 24 * 7;
      return g_strdup_printf (ngettext ("%d week ago",
        "%d weeks ago", seconds), seconds);
    }
  else
    {
      seconds /= 60 * 60 * 24 * 30;
      return g_strdup_printf (ngettext ("%d month ago",
        "%d months ago", seconds), seconds);
    }
}
