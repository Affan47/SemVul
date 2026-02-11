_log_fatal_handler (const char *domain,
   GLogLevelFlags flags,
   const char *message,
   gpointer user_data)
{
  gboolean suppress = _log_should_suppress (domain, flags, message);

  if (!suppress)
    g_on_error_stack_trace ("libtool --mode=exec gdb");

  return !suppress;
}
