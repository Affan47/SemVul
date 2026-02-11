_gnutls_strdup (const char *str)
{
  size_t siz = strlen (str) + 1;
  char *ret;

  ret = gnutls_malloc (siz);
  if (ret != NULL)
    memcpy (ret, str, siz);
  return ret;
}
