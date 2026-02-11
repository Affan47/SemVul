print_debug (const gchar *format, ...)
{
  gchar *s;
  va_list ap;
  gchar timebuf[64];
  GTimeVal now;
  time_t now_t;
  struct tm broken_down;
  static volatile gsize once_init_value = 0;
  static gboolean show_debug = FALSE;
  static guint pid = 0;

  if (g_once_init_enter (&once_init_value))
    {
      show_debug = (g_getenv ("HOTPLUG_SNIFFER_DEBUG") != NULL);
      pid = getpid ();
      g_once_init_leave (&once_init_value, 1);
    }

  if (!show_debug)
    goto out;

  g_get_current_time (&now);
  now_t = now.tv_sec;
  localtime_r (&now_t, &broken_down);
  strftime (timebuf, sizeof timebuf, "%H:%M:%S", &broken_down);

  va_start (ap, format);
  s = g_strdup_vprintf (format, ap);
  va_end (ap);

  g_print ("gnome-shell-hotplug-sniffer[%d]: %s.%03d: %s\n", pid, timebuf, (gint) (now.tv_usec / 1000), s);
  g_free (s);
 out:
  ;
}
