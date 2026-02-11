setup_dscp_client (GstMultiFdSink * sink, GstTCPClient * client)
{
  gint tos;
  gint ret;
  union gst_sockaddr
  {
    struct sockaddr sa;
    struct sockaddr_in6 sa_in6;
    struct sockaddr_storage sa_stor;
  } sa;
  socklen_t slen = sizeof (sa);
  gint af;


  if (sink->qos_dscp < 0)
    return 0;

  if ((ret = getsockname (client->fd.fd, &sa.sa, &slen)) < 0) {
    GST_DEBUG_OBJECT (sink, "could not get sockname: %s", g_strerror (errno));
    return ret;
  }

  af = sa.sa.sa_family;


  if (af == AF_INET6) {

    GST_DEBUG_OBJECT (sink, "check IP6 socket");
    if (IN6_IS_ADDR_V4MAPPED (&(sa.sa_in6.sin6_addr))) {
      GST_DEBUG_OBJECT (sink, "mapped to IPV4");
      af = AF_INET;
    }
  }


  tos = (sink->qos_dscp & 0x3f) << 2;

  switch (af) {
    case AF_INET:
      ret = setsockopt (client->fd.fd, IPPROTO_IP, IP_TOS, &tos, sizeof (tos));
      break;
    case AF_INET6:
#ifdef IPV6_TCLASS
      ret =
          setsockopt (client->fd.fd, IPPROTO_IPV6, IPV6_TCLASS, &tos,
          sizeof (tos));
      break;
#endif
    default:
      ret = 0;
      GST_ERROR_OBJECT (sink, "unsupported AF");
      break;
  }
  if (ret)
    GST_DEBUG_OBJECT (sink, "could not set DSCP: %s", g_strerror (errno));

  return ret;
}
