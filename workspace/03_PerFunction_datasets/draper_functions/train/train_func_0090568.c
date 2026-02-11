mxml_fd_putc(int  ch,
             void *p)
{
  mxml_fdbuf_t	*buf;


  buf = (mxml_fdbuf_t *)p;

  if (buf->current >= buf->end)
    if (mxml_fd_write(buf) < 0)
      return (-1);

  if (ch < 0x80)
  {


    *(buf->current)++ = ch;
  }
  else if (ch < 0x800)
  {


    *(buf->current)++ = 0xc0 | (ch >> 6);
    *(buf->current)++ = 0x80 | (ch & 0x3f);
  }
  else if (ch < 0x10000)
  {


    *(buf->current)++ = 0xe0 | (ch >> 12);
    *(buf->current)++ = 0x80 | ((ch >> 6) & 0x3f);
    *(buf->current)++ = 0x80 | (ch & 0x3f);
  }
  else
  {


    *(buf->current)++ = 0xf0 | (ch >> 18);
    *(buf->current)++ = 0x80 | ((ch >> 12) & 0x3f);
    *(buf->current)++ = 0x80 | ((ch >> 6) & 0x3f);
    *(buf->current)++ = 0x80 | (ch & 0x3f);
  }


  return (0);
}
