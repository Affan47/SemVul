write(const void *buffer, size_t size)
{
  if (! (ctx && dir > 0))
    G_THROW( ERR_MSG("IFFByteStream.not_ready4") );
  if (seekto > offset)
    G_THROW( ERR_MSG("IFFByteStream.cant_write") );
  size_t bytes = bs->write(buffer, size);
  offset += bytes;
  return bytes;
}
