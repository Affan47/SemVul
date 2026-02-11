nautilus_debug_valist (DebugFlags flag,
                       const gchar *format,
                       va_list args)
{
  if (G_UNLIKELY(!initialized))
    nautilus_debug_set_flags_from_env ();

  if (flag & flags)
    g_logv (G_LOG_DOMAIN, G_LOG_LEVEL_DEBUG, format, args);
}
