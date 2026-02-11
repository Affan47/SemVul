gst_udpsrc_stop (GstBaseSrc * bsrc)
{
  GstUDPSrc *src;

  src = GST_UDPSRC (bsrc);

  GST_DEBUG ("stopping, closing sockets");

  if (src->used_socket) {
    if (src->auto_multicast
        &&
        g_inet_address_get_is_multicast (g_inet_socket_address_get_address
            (src->addr))) {
      GError *err = NULL;

      GST_DEBUG_OBJECT (src, "leaving multicast group %s", src->address);

      if (!g_socket_leave_multicast_group (src->used_socket,
              g_inet_socket_address_get_address (src->addr), FALSE,
              src->multi_iface, &err)) {
        GST_ERROR_OBJECT (src, "Failed to leave multicast group: %s",
            err->message);
        g_clear_error (&err);
      }
    }

    if (src->close_socket || !src->external_socket) {
      GError *err = NULL;
      if (!g_socket_close (src->used_socket, &err)) {
        GST_ERROR_OBJECT (src, "Failed to close socket: %s", err->message);
        g_clear_error (&err);
      }
    }

    g_object_unref (src->used_socket);
    src->used_socket = NULL;
    g_object_unref (src->addr);
    src->addr = NULL;
  }

  return TRUE;
}
