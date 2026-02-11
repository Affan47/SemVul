print_msg(
   const char *format,
   ...)
{
   char buffer[128];

   va_list ap;
   va_start(ap, format);
   snprintf(buffer, sizeof(buffer), "%s: %s", params->daemon, format);
#ifndef NO_DAEMON
   if (params->detached != 0)
      vsyslog(LOG_INFO, buffer, ap);
   else
#endif
   vfprintf(stderr, buffer, ap);
   va_end(ap);
}
