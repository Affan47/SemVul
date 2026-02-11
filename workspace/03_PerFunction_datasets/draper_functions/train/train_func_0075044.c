_dsa_generate_params (bigint_t * resarr, int *resarr_len, int bits)
{

  int ret;
  gcry_sexp_t parms, key, list;


  if (bits > 1024 && gcry_check_version ("1.3.1") == NULL)
    {
      gnutls_assert ();
      return GNUTLS_E_INVALID_REQUEST;
    }

  if (bits < 512)
    {
      gnutls_assert ();
      return GNUTLS_E_INVALID_REQUEST;
    }

  ret = gcry_sexp_build (&parms, NULL, "(genkey(dsa(nbits %d)))", bits);
  if (ret != 0)
    {
      gnutls_assert ();
      return GNUTLS_E_INTERNAL_ERROR;
    }


  ret = gcry_pk_genkey (&key, parms);
  gcry_sexp_release (parms);

  if (ret != 0)
    {
      gnutls_assert ();
      return GNUTLS_E_INTERNAL_ERROR;
    }

  list = gcry_sexp_find_token (key, "p", 0);
  if (list == NULL)
    {
      gnutls_assert ();
      gcry_sexp_release (key);
      return GNUTLS_E_INTERNAL_ERROR;
    }

  resarr[0] = gcry_sexp_nth_mpi (list, 1, GCRYMPI_FMT_USG);
  gcry_sexp_release (list);

  list = gcry_sexp_find_token (key, "q", 0);
  if (list == NULL)
    {
      gnutls_assert ();
      gcry_sexp_release (key);
      return GNUTLS_E_INTERNAL_ERROR;
    }

  resarr[1] = gcry_sexp_nth_mpi (list, 1, GCRYMPI_FMT_USG);
  gcry_sexp_release (list);

  list = gcry_sexp_find_token (key, "g", 0);
  if (list == NULL)
    {
      gnutls_assert ();
      gcry_sexp_release (key);
      return GNUTLS_E_INTERNAL_ERROR;
    }

  resarr[2] = gcry_sexp_nth_mpi (list, 1, GCRYMPI_FMT_USG);
  gcry_sexp_release (list);

  list = gcry_sexp_find_token (key, "y", 0);
  if (list == NULL)
    {
      gnutls_assert ();
      gcry_sexp_release (key);
      return GNUTLS_E_INTERNAL_ERROR;
    }

  resarr[3] = gcry_sexp_nth_mpi (list, 1, GCRYMPI_FMT_USG);
  gcry_sexp_release (list);


  list = gcry_sexp_find_token (key, "x", 0);
  if (list == NULL)
    {
      gnutls_assert ();
      gcry_sexp_release (key);
      return GNUTLS_E_INTERNAL_ERROR;
    }

  resarr[4] = gcry_sexp_nth_mpi (list, 1, GCRYMPI_FMT_USG);

  gcry_sexp_release (list);
  gcry_sexp_release (key);

  _gnutls_mpi_log ("p: ", resarr[0]);
  _gnutls_mpi_log ("q: ", resarr[1]);
  _gnutls_mpi_log ("g: ", resarr[2]);
  _gnutls_mpi_log ("y: ", resarr[3]);
  _gnutls_mpi_log ("x: ", resarr[4]);

  *resarr_len = 5;

  return 0;

}
