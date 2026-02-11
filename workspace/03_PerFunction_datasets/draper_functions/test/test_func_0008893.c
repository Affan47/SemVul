_gcry_kdf_scrypt (const unsigned char *passwd, size_t passwdlen,
                  int algo, int subalgo,
                  const unsigned char *salt, size_t saltlen,
                  unsigned long iterations,
                  size_t dkLen, unsigned char *DK)
{
  u64 N = subalgo;
  u32 r;
  u32 p = iterations;

  gpg_err_code_t ec;
  u32 i;
  unsigned char *B = NULL;
  unsigned char *tmp1 = NULL;
  unsigned char *tmp2 = NULL;
  size_t r128;
  size_t nbytes;

  if (subalgo < 1 || !iterations)
    return GPG_ERR_INV_VALUE;

  if (algo == GCRY_KDF_SCRYPT)
    r = 8;
  else if (algo == 41)
    r = 1;
  else
    return GPG_ERR_UNKNOWN_ALGORITHM;

  r128 = r * 128;
  if (r128 / 128 != r)
    return GPG_ERR_ENOMEM;

  nbytes = p * r128;
  if (r128 && nbytes / r128 != p)
    return GPG_ERR_ENOMEM;

  nbytes = N * r128;
  if (r128 && nbytes / r128 != N)
    return GPG_ERR_ENOMEM;

  nbytes = 64 + r128;
  if (nbytes < r128)
    return GPG_ERR_ENOMEM;

  B = xtrymalloc (p * r128);
  if (!B)
    {
      ec = gpg_err_code_from_syserror ();
      goto leave;
    }

  tmp1 = xtrymalloc (N * r128);
  if (!tmp1)
    {
      ec = gpg_err_code_from_syserror ();
      goto leave;
    }

  tmp2 = xtrymalloc (64 + r128);
  if (!tmp2)
    {
      ec = gpg_err_code_from_syserror ();
      goto leave;
    }

  ec = _gcry_kdf_pkdf2 (passwd, passwdlen, GCRY_MD_SHA256, salt, saltlen,
                        1 , p * r128, B);

  for (i = 0; !ec && i < p; i++)
    _scryptROMix (r, &B[i * r128], N, tmp1, tmp2);

  for (i = 0; !ec && i < p; i++)
    ec = _gcry_kdf_pkdf2 (passwd, passwdlen, GCRY_MD_SHA256, B, p * r128,
                          1 , dkLen, DK);

 leave:
  xfree (tmp2);
  xfree (tmp1);
  xfree (B);

  return ec;
}
