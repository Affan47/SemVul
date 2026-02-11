get_mtu_from_ssl(SSL* ssl)
{
  int ret = SOSO_MTU;
#if !defined(TURN_NO_DTLS)
  if(ssl)
	  ret = BIO_ctrl(SSL_get_wbio(ssl), BIO_CTRL_DGRAM_QUERY_MTU, 0, NULL);
#else
  UNUSED_ARG(ssl);
#endif
  return ret;
}
