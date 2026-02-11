_bfd_ar_sizepad (char *p, size_t n, bfd_size_type size)
{
  static char buf[21];
  size_t len;

  snprintf (buf, sizeof (buf), "%-10" BFD_VMA_FMT "u", size);
  len = strlen (buf);
  if (len > n)
    {
      bfd_set_error (bfd_error_file_too_big);
      return FALSE;
    }
  if (len < n)
    {
      memcpy (p, buf, len);
      memset (p + len, ' ', n - len);
    }
  else
    memcpy (p, buf, n);
  return TRUE;
}
