RTMPSockBuf_Close(RTMPSockBuf *sb)
{
#if defined(CRYPTO) && !defined(NO_SSL)
  if (sb->sb_ssl)
    {
      TLS_shutdown(sb->sb_ssl);
      TLS_close(sb->sb_ssl);
      sb->sb_ssl = NULL;
    }
#endif
  return closesocket(sb->sb_socket);
}
