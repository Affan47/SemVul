gst_udp_set_loop (int sockfd, guint16 ss_family, gboolean loop)
{
  int ret = -1;
  int l = (loop == FALSE) ? 0 : 1;

  switch (ss_family) {
    case AF_INET:
    {
      ret = setsockopt (sockfd, IPPROTO_IP, IP_MULTICAST_LOOP, &l, sizeof (l));
      if (ret < 0)
        return ret;

      break;
    }
    case AF_INET6:
    {
      ret =
          setsockopt (sockfd, IPPROTO_IPV6, IPV6_MULTICAST_LOOP, &l,
          sizeof (l));
      if (ret < 0)
        return ret;

      break;
    }
    default:
#ifdef G_OS_WIN32
      WSASetLastError (WSAEAFNOSUPPORT);
#else
      errno = EAFNOSUPPORT;
#endif
  }

  return ret;
}
