gnutls_x509_crt_get_extension_oid (gnutls_x509_crt_t cert, int indx,
                                   void *oid, size_t * sizeof_oid)
{
  int result;

  if (cert == NULL)
    {
      gnutls_assert ();
      return GNUTLS_E_INVALID_REQUEST;
    }

  result = _gnutls_x509_crt_get_extension_oid (cert, indx, oid, sizeof_oid);
  if (result < 0)
    {
      return result;
    }

  return 0;

}
