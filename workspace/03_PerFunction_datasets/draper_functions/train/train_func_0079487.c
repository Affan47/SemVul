selftest_encr_1024 (gcry_sexp_t pkey, gcry_sexp_t skey)
{
  const char *errtxt = NULL;
  gcry_error_t err;
  const unsigned int nbits = 1000;
  gcry_mpi_t plaintext = NULL;
  gcry_sexp_t plain = NULL;
  gcry_sexp_t encr  = NULL;
  gcry_mpi_t  ciphertext = NULL;
  gcry_sexp_t decr  = NULL;
  gcry_mpi_t  decr_plaintext = NULL;
  gcry_sexp_t tmplist = NULL;


  plaintext = mpi_new (nbits);
  _gcry_mpi_randomize (plaintext, nbits, GCRY_WEAK_RANDOM);


  err = sexp_build (&plain, NULL, "(data (flags raw) (value %m))", plaintext);
  if (err)
    {
      errtxt = "converting data failed";
      goto leave;
    }


  err = _gcry_pk_encrypt (&encr, plain, pkey);
  if (err)
    {
      errtxt = "encrypt failed";
      goto leave;
    }


  ciphertext = extract_a_from_sexp (encr);
  if (!ciphertext)
    {
      errtxt = "gcry_pk_decrypt returned garbage";
      goto leave;
    }


  if (!mpi_cmp (plaintext, ciphertext))
    {
      errtxt = "ciphertext matches plaintext";
      goto leave;
    }


  err = _gcry_pk_decrypt (&decr, encr, skey);
  if (err)
    {
      errtxt = "decrypt failed";
      goto leave;
    }


  tmplist = sexp_find_token (decr, "value", 0);
  if (tmplist)
    decr_plaintext = sexp_nth_mpi (tmplist, 1, GCRYMPI_FMT_USG);
  else
    decr_plaintext = sexp_nth_mpi (decr, 0, GCRYMPI_FMT_USG);
  if (!decr_plaintext)
    {
      errtxt = "decrypt returned no plaintext";
      goto leave;
    }


  if (mpi_cmp (plaintext, decr_plaintext))
    {
      errtxt = "mismatch";
      goto leave;
    }

 leave:
  sexp_release (tmplist);
  _gcry_mpi_release (decr_plaintext);
  sexp_release (decr);
  _gcry_mpi_release (ciphertext);
  sexp_release (encr);
  sexp_release (plain);
  _gcry_mpi_release (plaintext);
  return errtxt;
}
