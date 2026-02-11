_gnutls_gen_openpgp_certificate (gnutls_session_t session, opaque ** data)
{
  int ret;
  opaque *pdata;
  gnutls_cert *apr_cert_list;
  gnutls_privkey_t apr_pkey;
  int apr_cert_list_length;


  if ((ret =
       _gnutls_get_selected_cert (session, &apr_cert_list,
                                  &apr_cert_list_length, &apr_pkey)) < 0)
    {
      gnutls_assert ();
      return ret;
    }

  ret = 3 + 1 + 3;


  if (apr_cert_list_length > 0)
    {
      if (apr_cert_list[0].use_subkey != 0)
        ret += 1 + sizeof (apr_cert_list[0].subkey_id);

      ret += apr_cert_list[0].raw.size;
    }

  (*data) = gnutls_malloc (ret);
  pdata = (*data);

  if (pdata == NULL)
    {
      gnutls_assert ();
      return GNUTLS_E_MEMORY_ERROR;
    }

  _gnutls_write_uint24 (ret - 3, pdata);
  pdata += 3;


  if (apr_cert_list_length > 0)
    {
      if (apr_cert_list[0].use_subkey != 0)
        {
          *pdata = PGP_KEY_SUBKEY;
          pdata++;
          *pdata = sizeof (apr_cert_list[0].subkey_id);
          pdata++;
          memcpy (pdata, apr_cert_list[0].subkey_id,
                  sizeof (apr_cert_list[0].subkey_id));
          pdata += sizeof (apr_cert_list[0].subkey_id);
        }
      else
        {
          *pdata = PGP_KEY;
          pdata++;
        }

      _gnutls_write_datum24 (pdata, apr_cert_list[0].raw);
      pdata += (3 + apr_cert_list[0].raw.size);
    }
  else
    {
      *pdata = PGP_KEY;
      pdata++;
      _gnutls_write_uint24 (0, pdata);
    }

  return ret;
}
