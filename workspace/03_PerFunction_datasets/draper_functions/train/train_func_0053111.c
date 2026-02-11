_parse_safe_contents (ASN1_TYPE sc, const char *sc_name,
                      gnutls_pkcs12_bag_t bag)
{
  gnutls_datum_t content = { NULL, 0 };
  int result;


  result = _gnutls_x509_read_value (sc, sc_name, &content, 1);
  if (result < 0)
    {
      gnutls_assert ();
      goto cleanup;
    }

  result = _pkcs12_decode_safe_contents (&content, bag);
  if (result < 0)
    {
      gnutls_assert ();
      goto cleanup;
    }

  _gnutls_free_datum (&content);

  return 0;

cleanup:
  _gnutls_free_datum (&content);
  return result;
}
