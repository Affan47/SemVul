gnutls_x509_privkey_export_pkcs8 (gnutls_x509_privkey_t key,
                                  gnutls_x509_crt_fmt_t format,
                                  const char *password,
                                  unsigned int flags,
                                  void *output_data,
                                  size_t * output_data_size)
{
  ASN1_TYPE pkcs8_asn, pkey_info;
  int ret;
  gnutls_datum_t tmp;
  schema_id schema;

  if (key == NULL)
    {
      gnutls_assert ();
      return GNUTLS_E_INVALID_REQUEST;
    }


  ret = encode_to_private_key_info (key, &tmp, &pkey_info);
  if (ret < 0)
    {
      gnutls_assert ();
      return ret;
    }

  schema = _gnutls_pkcs_flags_to_schema (flags);

  if ((flags & GNUTLS_PKCS_PLAIN) || password == NULL)
    {
      _gnutls_free_datum (&tmp);

      ret =
        _gnutls_x509_export_int (pkey_info, format,
                                 PEM_UNENCRYPTED_PKCS8,
                                 output_data, output_data_size);

      asn1_delete_structure (&pkey_info);
    }
  else
    {
      asn1_delete_structure (&pkey_info);

      ret = encode_to_pkcs8_key (schema, &tmp, password, &pkcs8_asn);
      _gnutls_free_datum (&tmp);

      if (ret < 0)
        {
          gnutls_assert ();
          return ret;
        }

      ret =
        _gnutls_x509_export_int (pkcs8_asn, format, PEM_PKCS8,
                                 output_data, output_data_size);

      asn1_delete_structure (&pkcs8_asn);
    }

  return ret;
}
