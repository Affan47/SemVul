get_alt_name (gnutls_x509_crt_t cert, const char *extension_id,
              unsigned int seq, void *ret,
              size_t * ret_size, unsigned int *ret_type,
              unsigned int *critical, int othername_oid)
{
  int result;
  gnutls_datum_t dnsname;
  ASN1_TYPE c2 = ASN1_TYPE_EMPTY;
  gnutls_x509_subject_alt_name_t type;

  if (cert == NULL)
    {
      gnutls_assert ();
      return GNUTLS_E_INVALID_REQUEST;
    }

  if (ret)
    memset (ret, 0, *ret_size);
  else
    *ret_size = 0;

  if ((result =
       _gnutls_x509_crt_get_extension (cert, extension_id, 0, &dnsname,
                                       critical)) < 0)
    {
      return result;
    }

  if (dnsname.size == 0 || dnsname.data == NULL)
    {
      gnutls_assert ();
      return GNUTLS_E_REQUESTED_DATA_NOT_AVAILABLE;
    }

  if (strcmp ("2.5.29.17", extension_id) == 0)
    result = asn1_create_element (_gnutls_get_pkix (),
                                  "PKIX1.SubjectAltName", &c2);
  else if (strcmp ("2.5.29.18", extension_id) == 0)
    result = asn1_create_element (_gnutls_get_pkix (),
                                  "PKIX1.IssuerAltName", &c2);
  else
    {
      gnutls_assert ();
      return GNUTLS_E_INTERNAL_ERROR;
    }

  if (result != ASN1_SUCCESS)
    {
      gnutls_assert ();
      _gnutls_free_datum (&dnsname);
      return _gnutls_asn2err (result);
    }

  result = asn1_der_decoding (&c2, dnsname.data, dnsname.size, NULL);
  _gnutls_free_datum (&dnsname);

  if (result != ASN1_SUCCESS)
    {
      gnutls_assert ();
      asn1_delete_structure (&c2);
      return _gnutls_asn2err (result);
    }

  result =
    _gnutls_parse_general_name (c2, "", seq, ret, ret_size, ret_type,
                                othername_oid);

  asn1_delete_structure (&c2);

  if (result < 0)
    {
      gnutls_assert ();
      return result;
    }

  type = result;

  return type;
}
