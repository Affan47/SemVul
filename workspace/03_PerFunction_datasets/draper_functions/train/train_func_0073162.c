gnutls_x509_crq_get_key_id (gnutls_x509_crq_t crq, unsigned int flags,
                            unsigned char *output_data,
                            size_t * output_data_size)
{
  int pk, result = 0;
  gnutls_datum_t pubkey;

  if (crq == NULL)
    {
      gnutls_assert ();
      return GNUTLS_E_INVALID_REQUEST;
    }

  if (*output_data_size < 20)
    {
      *output_data_size = 20;
      return GNUTLS_E_SHORT_MEMORY_BUFFER;
    }

  pk = gnutls_x509_crq_get_pk_algorithm (crq, NULL);
  if (pk < 0)
    {
      gnutls_assert ();
      return pk;
    }

  if (pk == GNUTLS_PK_RSA || pk == GNUTLS_PK_DSA)
    {


      return rsadsa_crq_get_key_id (crq, pk, output_data, output_data_size);
    }

  pubkey.size = 0;
  result =
    asn1_der_coding (crq->crq, "certificationRequestInfo.subjectPKInfo", NULL,
                     &pubkey.size, NULL);
  if (result != ASN1_MEM_ERROR)
    {
      gnutls_assert ();
      return _gnutls_asn2err (result);
    }

  pubkey.data = gnutls_malloc (pubkey.size);
  if (pubkey.data == NULL)
    {
      gnutls_assert ();
      return GNUTLS_E_MEMORY_ERROR;
    }

  result =
    asn1_der_coding (crq->crq, "certificationRequestInfo.subjectPKInfo",
                     pubkey.data, &pubkey.size, NULL);
  if (result != ASN1_SUCCESS)
    {
      gnutls_assert ();
      gnutls_free (pubkey.data);
      return _gnutls_asn2err (result);
    }

  result = gnutls_fingerprint (GNUTLS_DIG_SHA1, &pubkey,
                               output_data, output_data_size);

  gnutls_free (pubkey.data);

  return result;
}
