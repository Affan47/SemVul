cmdret_new (int success, char *fmt, ...)
{
  cmdret *ret = xmalloc (sizeof (cmdret));
  va_list ap;

  ret->success = success;

  if (fmt)
    {
      va_start (ap, fmt);
      ret->output = xvsprintf (fmt, ap);
      va_end (ap);
    }
  else
    ret->output = NULL;

  return ret;
}
