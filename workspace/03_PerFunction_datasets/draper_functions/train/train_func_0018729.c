stream_read(STREAM *stream, char *buffer, int len)
{
  size_t eff_read;
  size_t len_read;

  while (len > 0)
  {
    len_read = Min(len, MAX_IO);
    eff_read = fread(buffer, 1, len_read, FD);

    if (eff_read > 0)
    {
      STREAM_eff_read += eff_read;
      len -= eff_read;
      buffer += eff_read;
    }

    if (eff_read < len_read)
    {
      if (feof(FD))
      {
        errno = 0;
        return TRUE;
      }
      if (ferror(FD) && errno != EINTR)
        return TRUE;
    }
  }

  return FALSE;
}
