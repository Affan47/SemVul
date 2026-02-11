displaymigration_crypt_sign_hash (struct rsa_key *k, char *hash, gchar **result)
{
  gcry_mpi_t mpi;
  gcry_sexp_t data, sig, key;
  int rc;
  char *hex;

  do_encode_md (hash, 20, GCRY_MD_SHA1, 1024, &mpi);

  if (gcry_sexp_build (&data, NULL, "(data (value %m))", mpi))
    return FALSE;

  gcry_mpi_release (mpi);

  if (gcry_sexp_build (&key, NULL, "(private-key (rsa (n %m) (e %m) (d %m) (p %m) (q %m) (u %m)))",
		       k->n, k->e, k->d, k->p, k->q, k->u))
    {
      gcry_sexp_release (data);
      return FALSE;
    }

  rc = gcry_pk_sign (&sig, data, key);

  gcry_sexp_release (data);
  gcry_sexp_release (key);

  if (rc)
    return FALSE;

  mpi = mpi_from_sexp (sig, "s");
  hex = hex_from_mpi (mpi);
  *result = g_strdup (hex);
  gcry_free (hex);
  gcry_mpi_release (mpi);
  gcry_sexp_release (sig);

  return TRUE;
}
