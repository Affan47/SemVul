ipvideo_decode_0xe (const GstMveDemuxStream * s, unsigned char *frame,
    const unsigned char **data, unsigned short *len)
{
  int y;
  unsigned char pix;


  CHECK_STREAM (len, 1);
  pix = *(*data)++;

  for (y = 0; y < 8; ++y) {
    memset (frame, pix, 8);
    frame += s->width;
  }

  return 0;
}
