Error(int sev, const char *message, ...)
{
  va_list ap;

  va_start(ap, message);


  if( g_console_ready ) CONSOLE.Warning(sev, message);
  else{
    vfprintf(stderr, message, ap);
    fflush(stderr);
  }
  va_end(ap);
}
