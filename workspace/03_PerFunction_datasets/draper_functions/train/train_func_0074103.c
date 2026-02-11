gnutls_pkcs11_token_set_pin (const char *token_url,
                             const char *oldpin,
                             const char *newpin, unsigned int flags)
{
  int ret;
  struct ck_function_list *module;
  ck_session_handle_t pks;
  struct p11_kit_uri *info = NULL;
  ck_rv_t rv;
  unsigned int ses_flags;

  ret = pkcs11_url_to_info (token_url, &info);
  if (ret < 0)
    {
      gnutls_assert ();
      return ret;
    }

  if (((flags & GNUTLS_PKCS11_PIN_USER) && oldpin == NULL) ||
      (flags & GNUTLS_PKCS11_PIN_SO))
    ses_flags = SESSION_WRITE | SESSION_LOGIN | SESSION_SO;
  else
    ses_flags = SESSION_WRITE | SESSION_LOGIN;

  ret = pkcs11_open_session (&module, &pks, info, ses_flags);
  p11_kit_uri_free (info);

  if (ret < 0)
    {
      gnutls_assert ();
      return ret;
    }

  if (oldpin == NULL)
    {
      rv = pkcs11_init_pin (module, pks, (char *) newpin, strlen (newpin));
      if (rv != CKR_OK)
        {
          gnutls_assert ();
          _gnutls_debug_log ("pkcs11: %s\n", pkcs11_strerror (rv));
          ret = pkcs11_rv_to_err (rv);
          goto finish;
        }
    }
  else
    {
      rv = pkcs11_set_pin (module, pks,
                           (char *) oldpin, strlen (oldpin),
                           (char *) newpin, strlen (newpin));
      if (rv != CKR_OK)
        {
          gnutls_assert ();
          _gnutls_debug_log ("pkcs11: %s\n", pkcs11_strerror (rv));
          ret = pkcs11_rv_to_err (rv);
          goto finish;
        }
    }

  ret = 0;

finish:
  pkcs11_close_session (module, pks);
  return ret;

}
