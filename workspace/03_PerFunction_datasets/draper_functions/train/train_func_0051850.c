tld_check_4 (const uint32_t * in, size_t inlen, size_t * errpos,
	     const Tld_table ** overrides)
{
  const Tld_table *tld;
  char *domain;
  int rc;

  if (errpos)
    *errpos = 0;


  rc = tld_get_4 (in, inlen, &domain);

  if (rc != TLD_SUCCESS)
    {
      if (rc == TLD_NO_TLD)
	return TLD_SUCCESS;
      else
	return rc;
    }


  tld = tld_default_table (domain, overrides);
  free (domain);

  return tld_check_4t (in, inlen, errpos, tld);
}
