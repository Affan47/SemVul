_gnutls_x509_ext_gen_key_id (const void *id, size_t id_size,
                             gnutls_datum_t * der_ext)
{
  ASN1_TYPE ext = ASN1_TYPE_EMPTY;
  int result;

  result =
    asn1_create_element (_gnutls_get_pkix (),
                         "PKIX1.SubjectKeyIdentifier", &ext);
  if (result != ASN1_SUCCESS)
    {
      gnutls_assert ();
      return _gnutls_asn2err (result);
    }

  result = asn1_write_value (ext, "", id, id_size);
  if (result != ASN1_SUCCESS)
    {
      gnutls_assert ();
      asn1_delete_structure (&ext);
      return _gnutls_asn2err (result);
    }

  result = _gnutls_x509_der_encode (ext, "", der_ext, 0);

  asn1_delete_structure (&ext);

  if (result < 0)
    {
      gnutls_assert ();
      return result;
    }

  return 0;
}
