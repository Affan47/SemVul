gst_dccp_server_wait_connections (GstElement * element, int server_sock_fd)
{

  int client_sock_fd;
  struct sockaddr_in client_address;
  socklen_t client_address_len;

  memset (&client_address, 0, sizeof (client_address));
  client_address_len = 0;

  if ((client_sock_fd =
          accept (server_sock_fd, (struct sockaddr *) &client_address,
              &client_address_len)) == -1) {
    GST_ELEMENT_ERROR (element, RESOURCE, OPEN_WRITE, (NULL),
        ("Could not accept client on server socket %d: %s (%d)",
            server_sock_fd, g_strerror (errno), errno));
    return -1;
  }

  GST_DEBUG_OBJECT (element, "Added new client ip %s with fd %d.",
      inet_ntoa (client_address.sin_addr), client_sock_fd);

  return client_sock_fd;
}
