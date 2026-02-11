_gcry_pk_util_get_rsa_use_e (gcry_sexp_t list, unsigned long *r_e)
{
  char buf[50];
  const char *s;
  size_t n;

  *r_e = 0;

  list = sexp_find_token (list, "rsa-use-e", 0);
  if (!list)
    {
      *r_e = 65537;
      return 0;
    }

  s = sexp_nth_data (list, 1, &n);
  if (!s || n >= DIM (buf) - 1 )
    {

      sexp_release (list);
      return GPG_ERR_INV_OBJ;
    }
  memcpy (buf, s, n);
  buf[n] = 0;
  *r_e = strtoul (buf, NULL, 0);
  sexp_release (list);
  return 0;
}
