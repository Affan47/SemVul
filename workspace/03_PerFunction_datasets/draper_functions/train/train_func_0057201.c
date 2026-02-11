gnutls_psk_set_server_credentials_hint (gnutls_psk_server_credentials_t res,
                                        const char *hint)
{
  res->hint = gnutls_strdup (hint);
  if (res->hint == NULL)
    {
      gnutls_assert ();
      return GNUTLS_E_MEMORY_ERROR;
    }

  return 0;
}
