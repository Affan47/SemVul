tpaw_debug (TpawDebugFlags flag,
    const gchar *format,
    ...)
{
  gchar *message;
  va_list args;

  va_start (args, format);
  message = g_strdup_vprintf (format, args);
  va_end (args);

  log_to_debug_sender (flag, message);

  if (flag & flags)
    g_log (G_LOG_DOMAIN, G_LOG_LEVEL_DEBUG, "%s", message);

  g_free (message);
}
