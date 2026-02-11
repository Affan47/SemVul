_idn2_u8_to_u32_nfc (const uint8_t * src, size_t srclen,
		     uint32_t ** out, size_t * outlen, int nfc)
{
  uint32_t *p;
  size_t plen;

  p = u8_to_u32 (src, srclen, NULL, &plen);
  if (p == NULL)
    {
      if (errno == ENOMEM)
	return IDN2_MALLOC;
      return IDN2_ENCODING_ERROR;
    }

  if (nfc)
    {
      size_t tmplen;
      uint32_t *tmp = u32_normalize (UNINORM_NFC, p, plen, NULL, &tmplen);
      free (p);
      if (tmp == NULL)
	{
	  if (errno == ENOMEM)
	    return IDN2_MALLOC;
	  return IDN2_NFC;
	}

      p = tmp;
      plen = tmplen;
    }

  *out = p;
  *outlen = plen;
  return IDN2_OK;
}
