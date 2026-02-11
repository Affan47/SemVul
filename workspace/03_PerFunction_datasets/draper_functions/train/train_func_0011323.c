gst_net_client_clock_start (GstNetClientClock * self)
{
  GSocketAddress *servaddr;
  GSocketAddress *myaddr;
  GSocketAddress *anyaddr;
  GInetAddress *inetaddr;
  GSocket *socket;
  GError *error = NULL;
  GSocketFamily family;

  g_return_val_if_fail (self->priv->address != NULL, FALSE);
  g_return_val_if_fail (self->priv->servaddr == NULL, FALSE);


  inetaddr = g_inet_address_new_from_string (self->priv->address);
  if (inetaddr == NULL)
    goto bad_address;

  family = g_inet_address_get_family (inetaddr);

  servaddr = g_inet_socket_address_new (inetaddr, self->priv->port);
  g_object_unref (inetaddr);

  g_assert (servaddr != NULL);

  GST_DEBUG_OBJECT (self, "will communicate with %s:%d", self->priv->address,
      self->priv->port);

  socket = g_socket_new (family, G_SOCKET_TYPE_DATAGRAM,
      G_SOCKET_PROTOCOL_UDP, &error);

  if (socket == NULL)
    goto no_socket;

  GST_DEBUG_OBJECT (self, "binding socket");
  inetaddr = g_inet_address_new_any (family);
  anyaddr = g_inet_socket_address_new (inetaddr, 0);
  g_socket_bind (socket, anyaddr, TRUE, &error);
  g_object_unref (anyaddr);
  g_object_unref (inetaddr);

  if (error != NULL)
    goto bind_error;


  myaddr = g_socket_get_local_address (socket, &error);

  if (myaddr == NULL)
    goto getsockname_error;

  GST_DEBUG_OBJECT (self, "socket opened on UDP port %hd",
      g_inet_socket_address_get_port (G_INET_SOCKET_ADDRESS (myaddr)));

  g_object_unref (myaddr);

  self->priv->cancel = g_cancellable_new ();
  self->priv->socket = socket;
  self->priv->servaddr = G_SOCKET_ADDRESS (servaddr);

  self->priv->thread = g_thread_try_new ("GstNetClientClock",
      gst_net_client_clock_thread, self, &error);

  if (error != NULL)
    goto no_thread;

  return TRUE;


no_socket:
  {
    GST_ERROR_OBJECT (self, "socket_new() failed: %s", error->message);
    g_error_free (error);
    return FALSE;
  }
bind_error:
  {
    GST_ERROR_OBJECT (self, "bind failed: %s", error->message);
    g_error_free (error);
    g_object_unref (socket);
    return FALSE;
  }
getsockname_error:
  {
    GST_ERROR_OBJECT (self, "get_local_address() failed: %s", error->message);
    g_error_free (error);
    g_object_unref (socket);
    return FALSE;
  }
bad_address:
  {
    GST_ERROR_OBJECT (self, "inet_address_new_from_string('%s') failed",
        self->priv->address);
    return FALSE;
  }
no_thread:
  {
    GST_ERROR_OBJECT (self, "could not create thread: %s", error->message);
    g_object_unref (self->priv->servaddr);
    self->priv->servaddr = NULL;
    g_object_unref (self->priv->socket);
    self->priv->socket = NULL;
    g_error_free (error);
    return FALSE;
  }
}
