tunnel_new_client (const char *host, int host_port,
		   const char *proxy, int proxy_port,
		   size_t content_length)
{
  const char *remote;
  int remote_port;
  Tunnel *tunnel;

  log_verbose ("tunnel_new_client (\"%s\", %d, \"%s\", %d, %d)",
	       host, host_port, proxy ? proxy : "(null)", proxy_port,
	       content_length);

  tunnel = malloc (sizeof (Tunnel));
  if (tunnel == NULL)
    {
      log_error ("tunnel_new_client: out of memory");
      return NULL;
    }

  tunnel->in_fd = -1;
  tunnel->out_fd = -1;
  tunnel->server_socket = -1;
  tunnel->dest.host_name = host;
  tunnel->dest.host_port = host_port;
  tunnel->dest.proxy_name = proxy;
  tunnel->dest.proxy_port = proxy_port;
  tunnel->dest.proxy_authorization = NULL;
  tunnel->dest.user_agent = NULL;

  tunnel->content_length = content_length - 1;
  tunnel->buf_ptr = tunnel->buf;
  tunnel->buf_len = 0;
  tunnel->in_total_raw = 0;
  tunnel->in_total_data = 0;
  tunnel->out_total_raw = 0;
  tunnel->out_total_data = 0;
  tunnel->strict_content_length = FALSE;
  tunnel->bytes = 0;

  if (tunnel->dest.proxy_name == NULL)
    {
      remote = tunnel->dest.host_name;
      remote_port = tunnel->dest.host_port;
    }
  else
    {
      remote = tunnel->dest.proxy_name;
      remote_port = tunnel->dest.proxy_port;
    }

  if (set_address (&tunnel->address, remote, remote_port) == -1)
    {
      log_error ("tunnel_new_client: set_address: %s", strerror (errno));
      free (tunnel);
      return NULL;
    }

  return tunnel;
}
