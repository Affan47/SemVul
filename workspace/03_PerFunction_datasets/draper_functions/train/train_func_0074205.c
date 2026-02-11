gst_multiudpsink_configure_client (GstMultiUDPSink * sink,
    GstUDPClient * client)
{
  GInetSocketAddress *saddr = G_INET_SOCKET_ADDRESS (client->addr);
  GInetAddress *addr = g_inet_socket_address_get_address (saddr);
  GSocketFamily family = g_socket_address_get_family (G_SOCKET_ADDRESS (saddr));
  GSocket *socket;
  GError *err = NULL;

  GST_DEBUG_OBJECT (sink, "configuring client %p", client);

  if (family == G_SOCKET_FAMILY_IPV6 && !sink->used_socket_v6)
    goto invalid_family;


  if (family == G_SOCKET_FAMILY_IPV6 || !sink->used_socket)
    socket = sink->used_socket_v6;
  else
    socket = sink->used_socket;

  if (g_inet_address_get_is_multicast (addr)) {
    GST_DEBUG_OBJECT (sink, "we have a multicast client %p", client);
    if (sink->auto_multicast) {
      GST_DEBUG_OBJECT (sink, "autojoining group");
      if (!g_socket_join_multicast_group (socket, addr, FALSE,
              sink->multi_iface, &err))
        goto join_group_failed;
    }
    GST_DEBUG_OBJECT (sink, "setting loop to %d", sink->loop);
    g_socket_set_multicast_loopback (socket, sink->loop);
    GST_DEBUG_OBJECT (sink, "setting ttl to %d", sink->ttl_mc);
    g_socket_set_multicast_ttl (socket, sink->ttl_mc);
  } else {
    GST_DEBUG_OBJECT (sink, "setting unicast ttl to %d", sink->ttl);
    g_socket_set_ttl (socket, sink->ttl);
  }
  return TRUE;


join_group_failed:
  {
    gst_multiudpsink_stop (GST_BASE_SINK (sink));
    GST_ELEMENT_ERROR (sink, RESOURCE, SETTINGS, (NULL),
        ("Could not join multicast group: %s",
            err ? err->message : "unknown reason"));
    g_clear_error (&err);
    return FALSE;
  }
invalid_family:
  {
    gst_multiudpsink_stop (GST_BASE_SINK (sink));
    GST_ELEMENT_ERROR (sink, RESOURCE, SETTINGS, (NULL),
        ("Invalid address family (got %d)", family));
    return FALSE;
  }
}
