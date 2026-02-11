gnutls_pkcs7_get_crl_raw (gnutls_pkcs7_t pkcs7,
                          int indx, void *crl, size_t * crl_size)
{
  ASN1_TYPE c2 = ASN1_TYPE_EMPTY;
  int result;
  char root2[ASN1_MAX_NAME_SIZE];
  gnutls_datum_t tmp = { NULL, 0 };
  int start, end;

  if (pkcs7 == NULL || crl_size == NULL)
    return GNUTLS_E_INVALID_REQUEST;


  result = _decode_pkcs7_signed_data (pkcs7->pkcs7, &c2, &tmp);
  if (result < 0)
    {
      gnutls_assert ();
      return result;
    }


  snprintf (root2, sizeof (root2), "crls.?%u", indx + 1);


  result = asn1_der_decoding_startEnd (c2, tmp.data, tmp.size,
                                       root2, &start, &end);

  if (result != ASN1_SUCCESS)
    {
      gnutls_assert ();
      result = _gnutls_asn2err (result);
      goto cleanup;
    }

  end = end - start + 1;

  if ((unsigned) end > *crl_size)
    {
      *crl_size = end;
      result = GNUTLS_E_SHORT_MEMORY_BUFFER;
      goto cleanup;
    }

  if (crl)
    memcpy (crl, &tmp.data[start], end);

  *crl_size = end;

  result = 0;

cleanup:
  _gnutls_free_datum (&tmp);
  if (c2)
    asn1_delete_structure (&c2);
  return result;
}
