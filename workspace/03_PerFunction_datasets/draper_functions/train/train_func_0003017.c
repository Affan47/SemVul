gst_tcp_host_to_ip (GstElement * element, const gchar * host)
{
  struct hostent *hostinfo;
  char **addrs;
  gchar *ip;
  struct in_addr addr;

  GST_DEBUG_OBJECT (element, "resolving host %s", host);


  if (inet_aton (host, &addr)) {
    ip = g_strdup (host);
    goto beach;
  }


  if (!(hostinfo = gethostbyname (host)))
    goto resolve_error;

  if (hostinfo->h_addrtype != AF_INET)
    goto not_ip;

  addrs = hostinfo->h_addr_list;


  ip = g_strdup (inet_ntoa (*(struct in_addr *) *addrs));

beach:
  GST_DEBUG_OBJECT (element, "resolved to IP %s", ip);
  return ip;

resolve_error:
  {
    GST_ELEMENT_ERROR (element, RESOURCE, NOT_FOUND, (NULL),
        ("Could not find IP address for host \"%s\".", host));
    return NULL;
  }
not_ip:
  {
    GST_ELEMENT_ERROR (element, RESOURCE, NOT_FOUND, (NULL),
        ("host \"%s\" is not an IP host", host));
    return NULL;
  }
}
