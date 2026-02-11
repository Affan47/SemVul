_gnutls_x509_raw_cert_to_gcert (gnutls_cert * gcert,
                                const gnutls_datum_t * derCert,
                                int flags  )
{
  int ret;
  gnutls_x509_crt_t cert;

  ret = gnutls_x509_crt_init (&cert);
  if (ret < 0)
    {
      gnutls_assert ();
      return ret;
    }

  ret = gnutls_x509_crt_import (cert, derCert, GNUTLS_X509_FMT_DER);
  if (ret < 0)
    {
      gnutls_assert ();
      gnutls_x509_crt_deinit (cert);
      return ret;
    }

  ret = _gnutls_x509_crt_to_gcert (gcert, cert, flags);
  gnutls_x509_crt_deinit (cert);

  return ret;
}
