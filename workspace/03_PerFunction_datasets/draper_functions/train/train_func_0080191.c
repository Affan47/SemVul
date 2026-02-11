gnutls_strerror (int error)
{
  const char *ret = NULL;
  const gnutls_error_entry *p;

  for (p = error_algorithms; p->desc != NULL; p++)
    {
      if (p->number == error)
        {
          ret = p->desc;
          break;
        }
    }


  if (ret == NULL)
    return _("(unknown error code)");

  return _(ret);
}
