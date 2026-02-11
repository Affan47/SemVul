gnutls_pkcs7_import (gnutls_pkcs7_t pkcs7, const gnutls_datum_t * data,
                     gnutls_x509_crt_fmt_t format)
{
  int result = 0, need_free = 0;
  gnutls_datum_t _data;

  if (pkcs7 == NULL)
    return GNUTLS_E_INVALID_REQUEST;

  _data.data = data->data;
  _data.size = data->size;


  if (format == GNUTLS_X509_FMT_PEM)
    {
      opaque *out;

      result = _gnutls_fbase64_decode (PEM_PKCS7, data->data, data->size,
                                       &out);

      if (result <= 0)
        {
          if (result == 0)
            result = GNUTLS_E_INTERNAL_ERROR;
          gnutls_assert ();
          return result;
        }

      _data.data = out;
      _data.size = result;

      need_free = 1;
    }


  result = asn1_der_decoding (&pkcs7->pkcs7, _data.data, _data.size, NULL);
  if (result != ASN1_SUCCESS)
    {
      result = _gnutls_asn2err (result);
      gnutls_assert ();
      goto cleanup;
    }

  if (need_free)
    _gnutls_free_datum (&_data);

  return 0;

cleanup:
  if (need_free)
    _gnutls_free_datum (&_data);
  return result;
}
