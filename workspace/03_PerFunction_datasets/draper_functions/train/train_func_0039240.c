RTMP_TLS_Accept(RTMP *r, void *ctx)
{
#if defined(CRYPTO) && !defined(NO_SSL)
  TLS_server(ctx, r->m_sb.sb_ssl);
  TLS_setfd(r->m_sb.sb_ssl, r->m_sb.sb_socket);
  if (TLS_accept(r->m_sb.sb_ssl) < 0)
    {
      RTMP_Log(RTMP_LOGERROR, "%s, TLS_Connect failed", __FUNCTION__);
      return FALSE;
    }
  return TRUE;
#else
  return FALSE;
#endif
}
