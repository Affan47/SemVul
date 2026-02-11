tunnel_write_or_padding (Tunnel *tunnel, Request request, void *data,
			 size_t length)
{
  static char padding[65536];
  size_t n, remaining;
  char *wdata = data;

  for (remaining = length; remaining > 0; remaining -= n, wdata += n)
    {
      if (tunnel->bytes + remaining > tunnel->content_length - sizeof_header &&
	  tunnel->content_length - tunnel->bytes > sizeof_header)
	n = tunnel->content_length - sizeof_header - tunnel->bytes;
      else if (remaining > tunnel->content_length - sizeof_header)
	n = tunnel->content_length - sizeof_header;
      else
	n = remaining;

      if (n > 65535)
	n = 65535;

      if (request == TUNNEL_PADDING)
	{
	  if (n + sizeof_header > remaining)
	    n = remaining - sizeof_header;
	  if (tunnel_write_request (tunnel, request, padding, n) == -1)
	    break;
	  n += sizeof_header;
	}
      else
	{
	  if (tunnel_write_request (tunnel, request, wdata, n) == -1)
	    break;
	}
    }

  return length - remaining;
}
