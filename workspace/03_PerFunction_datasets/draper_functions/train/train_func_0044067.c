_gnutls_max_record_pack (extension_priv_data_t epriv, gnutls_buffer_st * ps)
{
  int ret;

  BUFFER_APPEND_NUM (ps, epriv.num);

  return 0;

}
