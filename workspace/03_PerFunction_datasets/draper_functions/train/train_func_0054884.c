_gnutls_check_key_usage (const gnutls_cert * cert, gnutls_kx_algorithm_t alg)
{
  unsigned int key_usage = 0;
  int encipher_type;

  if (cert == NULL)
    {
      gnutls_assert ();
      return GNUTLS_E_INTERNAL_ERROR;
    }

  if (_gnutls_map_kx_get_cred (alg, 1) == GNUTLS_CRD_CERTIFICATE ||
      _gnutls_map_kx_get_cred (alg, 0) == GNUTLS_CRD_CERTIFICATE)
    {

      key_usage = cert->key_usage;

      encipher_type = _gnutls_kx_encipher_type (alg);

      if (key_usage != 0 && encipher_type != CIPHER_IGN)
        {


          if (encipher_type == CIPHER_ENCRYPT)
            {


              if (!(key_usage & GNUTLS_KEY_KEY_ENCIPHERMENT))
                {
                  gnutls_assert ();
                  return GNUTLS_E_KEY_USAGE_VIOLATION;
                }
            }

          if (encipher_type == CIPHER_SIGN)
            {


              if (!(key_usage & GNUTLS_KEY_DIGITAL_SIGNATURE))
                {
                  gnutls_assert ();
                  return GNUTLS_E_KEY_USAGE_VIOLATION;
                }
            }
        }
    }
  return 0;
}
