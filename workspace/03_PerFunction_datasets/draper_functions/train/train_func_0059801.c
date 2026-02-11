gnutls_x509_crl_get_raw_issuer_dn (gnutls_x509_crl_t crl,
				   gnutls_datum_t * dn)
{
  ASN1_TYPE c2 = ASN1_TYPE_EMPTY;
  int result, len1;
  int start1, end1;
  gnutls_datum_t crl_signed_data;

  if (crl == NULL)
    {
      gnutls_assert ();
      return GNUTLS_E_INVALID_REQUEST;
    }


  if ((result =
       asn1_create_element (_gnutls_get_pkix (), "PKIX1.TBSCertList",
                            &c2)) != ASN1_SUCCESS)
    {
      gnutls_assert ();
      return _gnutls_asn2err (result);
    }

  result =
    _gnutls_x509_get_signed_data (crl->crl, "tbsCertList", &crl_signed_data);
  if (result < 0)
    {
      gnutls_assert ();
      goto cleanup;
    }

  result =
    asn1_der_decoding (&c2, crl_signed_data.data, crl_signed_data.size, NULL);
  if (result != ASN1_SUCCESS)
    {

      gnutls_assert ();
      asn1_delete_structure (&c2);
      result = _gnutls_asn2err (result);
      goto cleanup;
    }

  result =
    asn1_der_decoding_startEnd (c2, crl_signed_data.data,
                                crl_signed_data.size, "issuer",
                                &start1, &end1);

  if (result != ASN1_SUCCESS)
    {
      gnutls_assert ();
      result = _gnutls_asn2err (result);
      goto cleanup;
    }

  len1 = end1 - start1 + 1;

  _gnutls_set_datum (dn, &crl_signed_data.data[start1], len1);

  result = 0;

cleanup:
  asn1_delete_structure (&c2);
  _gnutls_free_datum (&crl_signed_data);
  return result;
}
