do_read(bgav_input_context_t* ctx,
                   uint8_t * buffer, int len, int block)
  {
  mms_priv_t * priv;


  int bytes_to_copy;
  int bytes_read;

  priv = ctx->priv;

  bytes_read = 0;
  while(bytes_read < len)
    {
    if(!priv->buffer_size)
      {
      priv->buffer = bgav_mms_read_data(priv->mms, &priv->buffer_size, block);
      if(!priv->buffer)
        return bytes_read;
      priv->buffer_ptr = priv->buffer;
      }

    bytes_to_copy = __MIN(len - bytes_read, priv->buffer_size);
    memcpy(buffer + bytes_read, priv->buffer_ptr, bytes_to_copy);
    priv->buffer_ptr += bytes_to_copy;
    priv->buffer_size -= bytes_to_copy;
    bytes_read += bytes_to_copy;
    }

  return bytes_read;
  }
