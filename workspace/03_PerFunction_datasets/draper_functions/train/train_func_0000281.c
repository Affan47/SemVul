_gnutls_pkcs1_rsa_decrypt (gnutls_datum_t * plaintext,
                           const gnutls_datum_t * ciphertext,
                           bigint_t * params, unsigned params_len,
                           unsigned btype)
{
  unsigned int k, i;
  int ret;
  size_t esize, mod_bits;
  gnutls_pk_params_st pk_params;

  if (params_len > GNUTLS_MAX_PK_PARAMS)
    return gnutls_assert_val(GNUTLS_E_INTERNAL_ERROR);

  for (i = 0; i < params_len; i++)
    pk_params.params[i] = params[i];
  pk_params.params_nr = params_len;

  mod_bits = _gnutls_mpi_get_nbits (params[0]);
  k = mod_bits / 8;
  if (mod_bits % 8 != 0)
    k++;

  esize = ciphertext->size;

  if (esize != k)
    {
      gnutls_assert ();
      return GNUTLS_E_PK_DECRYPTION_FAILED;
    }


  if (btype == 2)
    {
      ret =
        _gnutls_pk_decrypt (GNUTLS_PK_RSA, plaintext, ciphertext, &pk_params);
    }
  else
    {
      ret =
        _gnutls_pk_encrypt (GNUTLS_PK_RSA, plaintext, ciphertext, &pk_params);
    }

  if (ret < 0)
    {
      gnutls_assert ();
      return ret;
    }


  if (plaintext->data[0] != 0 || plaintext->data[1] != btype)
    {
      gnutls_assert ();
      return GNUTLS_E_DECRYPTION_FAILED;
    }

  ret = GNUTLS_E_DECRYPTION_FAILED;
  switch (btype)
    {
    case 2:
      for (i = 2; i < plaintext->size; i++)
        {
          if (plaintext->data[i] == 0)
            {
              ret = 0;
              break;
            }
        }
      break;
    case 1:
      for (i = 2; i < plaintext->size; i++)
        {
          if (plaintext->data[i] == 0 && i > 2)
            {
              ret = 0;
              break;
            }
          if (plaintext->data[i] != 0xff)
            {
              _gnutls_handshake_log ("PKCS #1 padding error");
              _gnutls_free_datum (plaintext);


              break;
            }
        }
      break;
    default:
      gnutls_assert ();
      _gnutls_free_datum (plaintext);
      break;
    }
  i++;

  if (ret < 0)
    {
      gnutls_assert ();
      _gnutls_free_datum (plaintext);
      return GNUTLS_E_DECRYPTION_FAILED;
    }

  memmove (plaintext->data, &plaintext->data[i], esize - i);
  plaintext->size = esize - i;

  return 0;
}
