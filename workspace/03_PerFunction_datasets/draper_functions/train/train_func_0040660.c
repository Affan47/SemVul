RTMP_Connect0(RTMP *r, struct sockaddr * service)
{
  int on = 1;
  r->m_sb.sb_timedout = FALSE;
  r->m_pausing = 0;
  r->m_fDuration = 0.0;

  r->m_sb.sb_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (r->m_sb.sb_socket != -1)
    {
      if (connect(r->m_sb.sb_socket, service, sizeof(struct sockaddr)) < 0)
	{
	  int err = GetSockError();
	  RTMP_Log(RTMP_LOGERROR, "%s, failed to connect socket. %d (%s)",
	      __FUNCTION__, err, strerror(err));
	  RTMP_Close(r);
	  return FALSE;
	}

      if (r->Link.socksport)
	{
	  RTMP_Log(RTMP_LOGDEBUG, "%s ... SOCKS negotiation", __FUNCTION__);
	  if (!SocksNegotiate(r))
	    {
	      RTMP_Log(RTMP_LOGERROR, "%s, SOCKS negotiation failed.", __FUNCTION__);
	      RTMP_Close(r);
	      return FALSE;
	    }
	}
    }
  else
    {
      RTMP_Log(RTMP_LOGERROR, "%s, failed to create socket. Error: %d", __FUNCTION__,
	  GetSockError());
      return FALSE;
    }


  {
    SET_RCVTIMEO(tv, r->Link.timeout);
    if (setsockopt
        (r->m_sb.sb_socket, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(tv)))
      {
        RTMP_Log(RTMP_LOGERROR, "%s, Setting socket timeout to %ds failed!",
	    __FUNCTION__, r->Link.timeout);
      }
  }

  setsockopt(r->m_sb.sb_socket, IPPROTO_TCP, TCP_NODELAY, (char *) &on, sizeof(on));
  if (r->Link.protocol & RTMP_FEATURE_HTTP)
    setsockopt(r->m_sb.sb_socket, SOL_SOCKET, SO_KEEPALIVE, (char *) &on, sizeof (on));

  return TRUE;
}
