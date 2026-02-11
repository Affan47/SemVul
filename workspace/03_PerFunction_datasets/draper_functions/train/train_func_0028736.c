gnutls_pk_get_id (const char *name)
{
  gnutls_pk_algorithm_t ret = GNUTLS_PK_UNKNOWN;
  const gnutls_pk_entry *p;

  for (p = pk_algorithms; p->name != NULL; p++)
    if (name && strcmp (p->name, name) == 0)
      {
        ret = p->id;
        break;
      }

  return ret;
}
