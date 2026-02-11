azflush (s, flush)
  azio_stream *s;
  int flush;
{
  int err;

  if (s->mode == 'r')
  {
    unsigned char buffer[AZHEADER_SIZE + AZMETA_BUFFER_SIZE];
    my_pread(s->file, (uchar*) buffer, AZHEADER_SIZE + AZMETA_BUFFER_SIZE, 0,
             MYF(0));
    read_header(s, buffer);

    return Z_OK;
  }
  else
  {
    s->forced_flushes++;
    err= do_flush(s, flush);

    if (err) return err;
    my_sync(s->file, MYF(0));
    return  s->z_err == Z_STREAM_END ? Z_OK : s->z_err;
  }
}
