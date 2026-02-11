httpWrite2(http_t     *http,
           const char *buffer,
	   size_t     length)
{
  ssize_t	bytes;


  DEBUG_printf(("httpWrite(http=%p, buffer=%p, length=%d)\n", http,
                buffer, length));


  if (http == NULL || buffer == NULL)
    return (-1);


  http->activity = time(NULL);


  if (length > 0)
  {
    if (http->wused && (length + http->wused) > sizeof(http->wbuffer))
    {
      DEBUG_printf(("    flushing buffer (wused=%d, length=%d)\n",
                    http->wused, length));

      httpFlushWrite(http);
    }

    if ((length + http->wused) <= sizeof(http->wbuffer))
    {


      DEBUG_printf(("    copying %d bytes to wbuffer...\n", length));

      memcpy(http->wbuffer + http->wused, buffer, length);
      http->wused += length;
      bytes = length;
    }
    else
    {


      DEBUG_printf(("    writing %d bytes to socket...\n", length));

      if (http->data_encoding == HTTP_ENCODE_CHUNKED)
	bytes = http_write_chunk(http, buffer, length);
      else
	bytes = http_write(http, buffer, length);

      DEBUG_printf(("    wrote %d bytes...\n", bytes));
    }

    if (http->data_encoding == HTTP_ENCODE_LENGTH)
      http->data_remaining -= bytes;
  }
  else
    bytes = 0;


  if ((http->data_encoding == HTTP_ENCODE_CHUNKED && length == 0) ||
      (http->data_encoding == HTTP_ENCODE_LENGTH && http->data_remaining == 0))
  {


    DEBUG_puts("httpWrite: changing states...");

    if (http->wused)
      httpFlushWrite(http);

    if (http->data_encoding == HTTP_ENCODE_CHUNKED)
    {


      http_write(http, "0\r\n\r\n", 5);


      http->data_encoding  = HTTP_ENCODE_LENGTH;
      http->data_remaining = 0;
    }

    if (http->state == HTTP_POST_RECV)
      http->state ++;
    else if (http->state == HTTP_PUT_RECV)
      http->state = HTTP_STATUS;
    else
      http->state = HTTP_WAITING;
  }

  return (bytes);
}
