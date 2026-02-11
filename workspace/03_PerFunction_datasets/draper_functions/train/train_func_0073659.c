file_ostream__write_mem (file_ostream_t stream, const void *data, size_t len)
{
  if (len > 0)
    fwrite (data, 1, len, stream->fp);
}
