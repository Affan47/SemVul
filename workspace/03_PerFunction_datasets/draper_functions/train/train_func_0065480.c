_gnutls_ext_unpack (gnutls_session_t session, gnutls_buffer_st * packed)
{
  int i, ret;
  extension_priv_data_t data;
  gnutls_ext_unpack_func unpack;
  int max_exts = 0;
  uint16_t type;
  int size_for_type, cur_pos;


  BUFFER_POP_NUM (packed, max_exts);
  for (i = 0; i < max_exts; i++)
    {
      BUFFER_POP_NUM (packed, type);
      BUFFER_POP_NUM (packed, size_for_type);

      cur_pos = packed->length;

      unpack = _gnutls_ext_func_unpack (type);
      if (unpack == NULL)
        {
          gnutls_assert ();
          return GNUTLS_E_PARSING_ERROR;
        }

      ret = unpack (packed, &data);
      if (ret < 0)
        {
          gnutls_assert ();
          return ret;
        }


      cur_pos = cur_pos - packed->length;
      if (cur_pos   != size_for_type)
        {
          gnutls_assert ();
          return GNUTLS_E_PARSING_ERROR;
        }

      _gnutls_ext_set_resumed_session_data (session, type, data);
    }

  return 0;

error:
  return ret;
}
