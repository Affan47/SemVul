gc_error (int status, int errnum, const char *fmt, ...)
{
  va_list arg_ptr;

  va_start (arg_ptr, fmt);
  log_logv (JNLIB_LOG_ERROR, fmt, arg_ptr);
  va_end (arg_ptr);

  if (errnum)
    log_printf (": %s\n", strerror (errnum));
  else
    log_printf ("\n");

  if (status)
    {
      log_printf (NULL);
      log_printf ("fatal error (exit status %i)\n", status);
      exit (status);
    }
}
