_bfd_ar_spacepad (char *p, size_t n, const char *fmt, long val)
{
  static char buf[20];
  size_t len;

  snprintf (buf, sizeof (buf), fmt, val);
  len = strlen (buf);
  if (len < n)
    {
      memcpy (p, buf, len);
      memset (p + len, ' ', n - len);
    }
  else
    memcpy (p, buf, n);
}
