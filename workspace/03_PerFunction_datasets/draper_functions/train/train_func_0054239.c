proc_rsa_client_kx (gnutls_session_t session, opaque * data,
                    size_t _data_size)
{
  gnutls_datum_t plaintext;
  gnutls_datum_t ciphertext;
  int ret, dsize;
  int randomize_key = 0;
  ssize_t data_size = _data_size;

  if (gnutls_protocol_get_version (session) == GNUTLS_SSL3)
    {


      ciphertext.data = data;
      ciphertext.size = data_size;
    }
  else
    {


      DECR_LEN (data_size, 2);
      ciphertext.data = &data[2];
      dsize = _gnutls_read_uint16 (data);

      if (dsize != data_size)
        {
          gnutls_assert ();
          return GNUTLS_E_UNEXPECTED_PACKET_LENGTH;
        }
      ciphertext.size = dsize;
    }

  ret =
    gnutls_privkey_decrypt_data (session->internals.selected_key, 0,
                                 &ciphertext, &plaintext);

  if (ret < 0 || plaintext.size != GNUTLS_MASTER_SIZE)
    {


      gnutls_assert ();
      _gnutls_x509_log ("auth_rsa: Possible PKCS #1 format attack\n");
      randomize_key = 1;
    }
  else
    {


      if (_gnutls_get_adv_version_major (session) != plaintext.data[0]
          || _gnutls_get_adv_version_minor (session) != plaintext.data[1])
        {


          gnutls_assert ();
          _gnutls_x509_log
            ("auth_rsa: Possible PKCS #1 version check format attack\n");
        }
    }

  if (randomize_key != 0)
    {
      session->key->key.size = GNUTLS_MASTER_SIZE;
      session->key->key.data = gnutls_malloc (session->key->key.size);
      if (session->key->key.data == NULL)
        {
          gnutls_assert ();
          return GNUTLS_E_MEMORY_ERROR;
        }


      ret = _gnutls_rnd (GNUTLS_RND_NONCE, session->key->key.data,
                         session->key->key.size);
      if (ret < 0)
        {
          gnutls_assert ();
          return ret;
        }

    }
  else
    {
      session->key->key.data = plaintext.data;
      session->key->key.size = plaintext.size;
    }


  session->key->key.data[0] = _gnutls_get_adv_version_major (session);
  session->key->key.data[1] = _gnutls_get_adv_version_minor (session);

  return 0;
}
