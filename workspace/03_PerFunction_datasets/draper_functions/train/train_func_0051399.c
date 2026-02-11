gst_tcp_client_src_start (GstBaseSrc * bsrc)
{
  GstTCPClientSrc *src = GST_TCP_CLIENT_SRC (bsrc);
  GError *err = NULL;
  GInetAddress *addr;
  GSocketAddress *saddr;
  GResolver *resolver;


  addr = g_inet_address_new_from_string (src->host);
  if (!addr) {
    GList *results;

    resolver = g_resolver_get_default ();

    results =
        g_resolver_lookup_by_name (resolver, src->host, src->cancellable, &err);
    if (!results)
      goto name_resolve;
    addr = G_INET_ADDRESS (g_object_ref (results->data));

    g_resolver_free_addresses (results);
    g_object_unref (resolver);
  }
#ifndef GST_DISABLE_GST_DEBUG
  {
    gchar *ip = g_inet_address_to_string (addr);

    GST_DEBUG_OBJECT (src, "IP address for host %s is %s", src->host, ip);
    g_free (ip);
  }
#endif

  saddr = g_inet_socket_address_new (addr, src->port);
  g_object_unref (addr);


  GST_DEBUG_OBJECT (src, "opening receiving client socket to %s:%d",
      src->host, src->port);

  src->socket =
      g_socket_new (g_socket_address_get_family (saddr), G_SOCKET_TYPE_STREAM,
      G_SOCKET_PROTOCOL_TCP, &err);
  if (!src->socket)
    goto no_socket;

  GST_DEBUG_OBJECT (src, "opened receiving client socket");
  GST_OBJECT_FLAG_SET (src, GST_TCP_CLIENT_SRC_OPEN);


  if (!g_socket_connect (src->socket, saddr, src->cancellable, &err))
    goto connect_failed;

  g_object_unref (saddr);

  return TRUE;

no_socket:
  {
    GST_ELEMENT_ERROR (src, RESOURCE, OPEN_READ, (NULL),
        ("Failed to create socket: %s", err->message));
    g_clear_error (&err);
    g_object_unref (saddr);
    return FALSE;
  }
name_resolve:
  {
    if (g_error_matches (err, G_IO_ERROR, G_IO_ERROR_CANCELLED)) {
      GST_DEBUG_OBJECT (src, "Cancelled name resolval");
    } else {
      GST_ELEMENT_ERROR (src, RESOURCE, OPEN_READ, (NULL),
          ("Failed to resolve host '%s': %s", src->host, err->message));
    }
    g_clear_error (&err);
    g_object_unref (resolver);
    return FALSE;
  }
connect_failed:
  {
    if (g_error_matches (err, G_IO_ERROR, G_IO_ERROR_CANCELLED)) {
      GST_DEBUG_OBJECT (src, "Cancelled connecting");
    } else {
      GST_ELEMENT_ERROR (src, RESOURCE, OPEN_READ, (NULL),
          ("Failed to connect to host '%s:%d': %s", src->host, src->port,
              err->message));
    }
    g_clear_error (&err);
    g_object_unref (saddr);
    gst_tcp_client_src_stop (GST_BASE_SRC (src));
    return FALSE;
  }
}
