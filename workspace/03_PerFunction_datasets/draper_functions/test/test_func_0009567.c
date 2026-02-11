gnutls_pkcs7_delete_crt (gnutls_pkcs7_t pkcs7, int indx)
{
  ASN1_TYPE c2 = ASN1_TYPE_EMPTY;
  int result;
  char root2[ASN1_MAX_NAME_SIZE];

  if (pkcs7 == NULL)
    return GNUTLS_E_INVALID_REQUEST;


  result = _decode_pkcs7_signed_data (pkcs7->pkcs7, &c2, NULL);
  if (result < 0)
    {
      gnutls_assert ();
      return result;
    }


  snprintf (root2, sizeof (root2), "certificates.?%u", indx + 1);

  result = asn1_write_value (c2, root2, NULL, 0);
  if (result != ASN1_SUCCESS)
    {
      gnutls_assert ();
      result = _gnutls_asn2err (result);
      goto cleanup;
    }


  result =
    _gnutls_x509_der_encode_and_copy (c2, "", pkcs7->pkcs7, "content", 0);
  if (result < 0)
    {
      gnutls_assert ();
      goto cleanup;
    }

  asn1_delete_structure (&c2);

  return 0;

cleanup:
  if (c2)
    asn1_delete_structure (&c2);
  return result;
}
