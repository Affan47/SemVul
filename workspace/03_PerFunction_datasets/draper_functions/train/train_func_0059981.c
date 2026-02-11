ijs_recv_buf (IjsRecvChan *ch)
{
  int nbytes;
  int data_size;

  nbytes = ijs_recv_read (ch, ch->buf, 8);
  if (nbytes != 8)
    return IJS_EIO;
  ch->buf_size = ijs_get_int (ch->buf + 4);
  if (ch->buf_size < 8 || ch->buf_size > (int)sizeof(ch->buf))
    return IJS_ERANGE;
  data_size = ch->buf_size - 8;
  if (data_size > 0)
    {
      nbytes = ijs_recv_read (ch, ch->buf + 8, data_size);
      if (nbytes != data_size)
	return IJS_EIO;
    }
  ch->buf_idx = 8;
  return 0;
}
