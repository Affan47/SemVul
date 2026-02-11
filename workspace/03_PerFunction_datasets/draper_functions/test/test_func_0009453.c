evd_socket_check_address (EvdSocket       *self,
                          GSocketAddress  *address,
                          GError         **error)
{
  if (self->priv->family == G_SOCKET_FAMILY_INVALID)
    self->priv->family = g_socket_address_get_family (address);
  else if (self->priv->family != g_socket_address_get_family (address))
    {
      if (error != NULL)
        *error = g_error_new (G_IO_ERROR,
                              G_IO_ERROR_INVALID_ARGUMENT,
                              "Socket family and address family mismatch");

      return FALSE;
    }

  if (self->priv->type == G_SOCKET_TYPE_INVALID)
    {
      if (self->priv->protocol == G_SOCKET_PROTOCOL_UDP)
        self->priv->type = G_SOCKET_TYPE_DATAGRAM;
      else
        self->priv->type = G_SOCKET_TYPE_STREAM;
    }

  if (self->priv->protocol == G_SOCKET_PROTOCOL_UNKNOWN)
    self->priv->protocol = G_SOCKET_PROTOCOL_DEFAULT;

  return TRUE;
}
