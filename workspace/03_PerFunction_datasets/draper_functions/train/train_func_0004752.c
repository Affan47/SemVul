gnutls_pkcs11_init (unsigned int flags, const char *deprecated_config_file)
{
  int ret = 0;

  if (init != 0)
    {
      init++;
      return 0;
    }
  init++;

  p11_kit_pin_register_callback (P11_KIT_PIN_FALLBACK, p11_kit_pin_file_callback,
                                 NULL, NULL);

  if (flags == GNUTLS_PKCS11_FLAG_AUTO)
    {
      if (deprecated_config_file == NULL)
        ret = initialize_automatic_p11_kit ();

      if (ret == 0)
        ret = initialize_automatic_legacy (deprecated_config_file);
    }

  return ret;
}
