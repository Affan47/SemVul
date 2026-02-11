azclose (azio_stream *s)
{

  if (s == NULL) return Z_STREAM_ERROR;

  if (s->file < 1) return Z_OK;

  if (s->mode == 'w')
  {
    if (do_flush(s, Z_FINISH) != Z_OK)
      return destroy(s);

    putLong(s->file, s->crc);
    putLong(s->file, (uLong)(s->in & 0xffffffff));
    s->dirty= AZ_STATE_CLEAN;
    s->check_point= my_tell(s->file, MYF(0));
    write_header(s);
  }

  return destroy(s);
}
