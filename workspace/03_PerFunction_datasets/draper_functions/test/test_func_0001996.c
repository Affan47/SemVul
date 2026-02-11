rfc2068_get_next_file_chunk (gftp_request * request, char *buf, size_t size)
{
  rfc2068_params * params;
  size_t len;

  g_return_val_if_fail (request != NULL, GFTP_EFATAL);

  params = request->protocol_data;
  if (params->rbuf != NULL && params->rbuf->curpos != NULL)
    {
      len = params->rbuf->cur_bufsize > size ? size : params->rbuf->cur_bufsize;
      memcpy (buf, params->rbuf->curpos, len);

      if (len == params->rbuf->cur_bufsize)
        gftp_free_getline_buffer (&params->rbuf);
      else
        {
          params->rbuf->curpos += len;
          params->rbuf->cur_bufsize -= len;
        }

      return (len);
    }

  return (request->read_function (request, buf, size, request->datafd));
}
