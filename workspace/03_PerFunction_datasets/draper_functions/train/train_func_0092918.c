GNUNET_CRYPTO_rsa_sign (const struct GNUNET_CRYPTO_RsaPrivateKey *key,
                        const struct GNUNET_CRYPTO_RsaSignaturePurpose *purpose,
                        struct GNUNET_CRYPTO_RsaSignature *sig)
{
  gcry_sexp_t result;
  gcry_sexp_t data;
  size_t ssize;
  gcry_mpi_t rval;
  GNUNET_HashCode hc;
  char *buff;
  int bufSize;

  GNUNET_CRYPTO_hash (purpose, ntohl (purpose->size), &hc);
#define FORMATSTRING "(4:data(5:flags5:pkcs1)(4:hash6:sha51264:0123456789012345678901234567890123456789012345678901234567890123))"
  bufSize = strlen (FORMATSTRING) + 1;
  buff = GNUNET_malloc (bufSize);
  memcpy (buff, FORMATSTRING, bufSize);
  memcpy (&buff
          [bufSize -
           strlen
           ("0123456789012345678901234567890123456789012345678901234567890123))")
           - 1], &hc, sizeof (GNUNET_HashCode));
  GNUNET_assert (0 == gcry_sexp_new (&data, buff, bufSize, 0));
  GNUNET_free (buff);
  GNUNET_assert (0 == gcry_pk_sign (&result, data, key->sexp));
  gcry_sexp_release (data);
  GNUNET_assert (0 == key_from_sexp (&rval, result, "rsa", "s"));
  gcry_sexp_release (result);
  ssize = sizeof (struct GNUNET_CRYPTO_RsaSignature);
  GNUNET_assert (0 ==
                 gcry_mpi_print (GCRYMPI_FMT_USG, (unsigned char *) sig, ssize,
                                 &ssize, rval));
  gcry_mpi_release (rval);
  adjust (sig->sig, ssize, sizeof (struct GNUNET_CRYPTO_RsaSignature));
  return GNUNET_OK;
}
