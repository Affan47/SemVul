gnutls_pkcs11_token_get_url (unsigned int seq,
                             gnutls_pkcs11_url_type_t detailed, char **url)
{
  int ret;
  struct token_num tn;

  memset (&tn, 0, sizeof (tn));
  tn.seq = seq;
  tn.info = p11_kit_uri_new ();

  ret = _pkcs11_traverse_tokens (find_token_num, &tn, NULL, 0);
  if (ret < 0)
    {
      p11_kit_uri_free (tn.info);
      gnutls_assert ();
      return ret;
    }

  ret = pkcs11_info_to_url (tn.info, detailed, url);
  p11_kit_uri_free (tn.info);

  if (ret < 0)
    {
      gnutls_assert ();
      return ret;
    }

  return 0;

}
