mpg123_get_xing_header(xing_header_t * xing, unsigned char *buf)
{
  int i, head_flags;
  int id, mode;

  memset(xing, 0, sizeof(xing_header_t));


  id = (buf[1] >> 3) & 1;
  mode = (buf[3] >> 6) & 3;
  buf += 4;


  if (id)
    {

      if (mode != 3)
	buf += 32;
      else
	buf += 17;
    }
  else
    {

      if (mode != 3)
	buf += 17;
      else
	buf += 9;
    }

  if (strncmp((char *) buf, "Xing", 4))
    return 0;
  buf += 4;

  head_flags = GET_INT32BE(buf);

  if (head_flags & FRAMES_FLAG)
    xing->frames = GET_INT32BE(buf);
  if (xing->frames < 1)
    xing->frames = 1;
  if (head_flags & BYTES_FLAG)
    xing->bytes = GET_INT32BE(buf);

  if (head_flags & TOC_FLAG)
    {
      for (i = 0; i < 100; i++)
	xing->toc[i] = buf[i];
      buf += 100;
    }

#ifdef XING_DEBUG
  for (i = 0; i < 100; i++)
    {
      if ((i % 10) == 0)
	fprintf(stderr, "\n");
      fprintf(stderr, " %3d", xing->toc[i]);
    }
#endif

  return 1;
}
