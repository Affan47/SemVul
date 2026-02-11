ia_pack (extension_priv_data_t epriv, gnutls_buffer_st * ps)
{
  ia_ext_st *priv = epriv.ptr;
  int ret;

  BUFFER_APPEND_NUM (ps, priv->flags);
  BUFFER_APPEND_PFX (ps, priv->inner_secret, GNUTLS_MASTER_SIZE);

  return 0;
}
