tld_get_4 (const uint32_t * in, size_t inlen, char **out)
{
  const uint32_t *ipos;
  size_t olen;

  *out = NULL;
  if (!in || inlen == 0)
    return TLD_NODATA;

  ipos = &in[inlen - 1];
  olen = 0;

  while (ipos >= in && ((*ipos >= 0x41 && *ipos <= 0x5A) ||
			(*ipos >= 0x61 && *ipos <= 0x7A)))
    ipos--, olen++;

  if (olen > 0 && ipos >= in && DOTP (*ipos))
    {

      char *out_s = malloc (sizeof (char) * (olen + 1));
      char *opos = out_s;

      if (!opos)
	return TLD_MALLOC_ERROR;

      ipos++;

      for (; ipos < &in[inlen]; ipos++, opos++)
	*opos = *ipos > 0x5A ? *ipos : *ipos + 0x20;
      *opos = 0;
      *out = out_s;
      return TLD_SUCCESS;
    }

  return TLD_NO_TLD;
}
