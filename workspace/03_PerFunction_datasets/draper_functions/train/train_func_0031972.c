net_output_data (const char *format, ...)
{
  va_list args;
  size_t remaining, ret;

  va_start (args, format);
  remaining = BUFSIZ - (nfrontp - netobuf);

  if (strlen (format) > remaining || BUFSIZ / 4 > remaining)
    {
      netflush ();
      remaining = BUFSIZ - (nfrontp - netobuf);
    }
  ret = vsnprintf (nfrontp, remaining, format, args);
  nfrontp += ((ret < remaining - 1) ? ret : remaining - 1);
  va_end (args);
  return ret;
}
