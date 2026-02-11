HTTP_Post(RTMP *r, RTMPTCmd cmd, const char *buf, int len)
{
  char hbuf[512];
  int hlen = snprintf(hbuf, sizeof(hbuf), "POST /%s%s/%d HTTP/1.1\r\n"
    "Host: %.*s:%d\r\n"
    "Accept: */*\r\n"
    "User-Agent: Shockwave Flash\n"
    "Connection: Keep-Alive\n"
    "Cache-Control: no-cache\r\n"
    "Content-type: application/x-fcs\r\n"
    "Content-length: %d\r\n\r\n", RTMPT_cmds[cmd],
    r->m_clientID.av_val ? r->m_clientID.av_val : "",
    r->m_msgCounter, r->Link.hostname.av_len, r->Link.hostname.av_val,
    r->Link.port, len);
  RTMPSockBuf_Send(&r->m_sb, hbuf, hlen);
  hlen = RTMPSockBuf_Send(&r->m_sb, buf, len);
  r->m_msgCounter++;
  r->m_unackd++;
  return hlen;
}
