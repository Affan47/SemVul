read_error_info (pixma_t * s, void *buf, unsigned size)
{
  unsigned len = 16;
  mp750_t *mp = (mp750_t *) s->subdriver;
  uint8_t *data;
  int error;

  data = pixma_newcmd (&mp->cb, cmd_error_info, 0, len);
  error = pixma_exec (s, &mp->cb);
  if (error >= 0 && buf)
    {
      if (len < size)
        size = len;

      memcpy (buf, data, size);
      error = len;
    }
  return error;
}
