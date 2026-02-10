gnutls_x509_crt_set_proxy_dn (gnutls_x509_crt_t crt, gnutls_x509_crt_t eecrt,
                              unsigned int raw_flag, const void *name,
                              unsigned int sizeof_name)
{
  int result;

  if (crt == NULL || eecrt == NULL)
    {
      return GNUTLS_E_INVALID_REQUEST;
    }

  result = asn1_copy_node (crt->cert, "tbsCertificate.subject",
                           eecrt->cert, "tbsCertificate.subject");
  if (result != ASN1_SUCCESS)
    {
      gnutls_assert ();
      return _gnutls_asn2err (result);
    }

  if (name && sizeof_name)
    {
      return _gnutls_x509_set_dn_oid (crt->cert, "tbsCertificate.subject",
                                      GNUTLS_OID_X520_COMMON_NAME,
                                      raw_flag, name, sizeof_name);
    }

  return 0;
}
