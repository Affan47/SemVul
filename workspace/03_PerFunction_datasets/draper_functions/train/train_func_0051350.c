gnutls_x509_crt_set_crl_dist_points2 (gnutls_x509_crt_t crt,
                                      gnutls_x509_subject_alt_name_t type,
                                      const void *data,
                                      unsigned int data_size,
                                      unsigned int reason_flags)
{
  int result;
  gnutls_datum_t der_data = { NULL, 0 };
  gnutls_datum_t oldname = { NULL, 0 };
  unsigned int critical;

  if (crt == NULL)
    {
      gnutls_assert ();
      return GNUTLS_E_INVALID_REQUEST;
    }


  result =
    _gnutls_x509_crt_get_extension (crt, "2.5.29.31", 0, &oldname, &critical);

  _gnutls_free_datum (&oldname);

  if (result != GNUTLS_E_REQUESTED_DATA_NOT_AVAILABLE)
    {
      gnutls_assert ();
      return GNUTLS_E_INVALID_REQUEST;
    }


  result =
    _gnutls_x509_ext_gen_crl_dist_points (type, data, data_size,
                                          reason_flags, &der_data);
  if (result < 0)
    {
      gnutls_assert ();
      return result;
    }

  result = _gnutls_x509_crt_set_extension (crt, "2.5.29.31", &der_data, 0);

  _gnutls_free_datum (&der_data);

  if (result < 0)
    {
      gnutls_assert ();
      return result;
    }

  crt->use_extensions = 1;

  return 0;

}
