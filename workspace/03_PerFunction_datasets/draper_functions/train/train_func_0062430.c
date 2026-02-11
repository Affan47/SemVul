stream_write(STREAM *stream, char *buffer, int len)
{
  size_t eff_write;
  size_t len_write;

	while (len > 0)
  {
    len_write = Min(len, MAX_IO);
    eff_write = fwrite(buffer, 1, len_write, FD);

    if (eff_write < len_write)
    {
      if (ferror(FD) && errno != EINTR)
        return TRUE;
    }

    len -= eff_write;
    buffer += eff_write;
  }

  if (EXEC_debug)
    return stream_flush(stream);
  else
    return FALSE;
}
