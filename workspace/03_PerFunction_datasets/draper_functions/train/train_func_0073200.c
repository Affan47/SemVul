if_file_read_callback (void *opaque, sc_byte *buffer, sc_int length)
{
  FILE *stream = (FILE *) opaque;
  sc_int bytes;

  bytes = fread (buffer, 1, length, stream);
  if (ferror (stream))
    sc_error ("if_file_read_callback: warning: read error\n");

  return bytes;
}
