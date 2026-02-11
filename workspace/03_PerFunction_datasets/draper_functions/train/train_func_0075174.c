ipvideo_decode_0xd (const GstMveDemuxStream * s, unsigned short *frame,
    const unsigned char **data, unsigned short *len)
{
  int x, y;
  unsigned short P[4];
  unsigned char index = 0;


  CHECK_STREAM (len, 8);

  P[0] = PIXEL (*data);
  (*data) += 2;
  P[1] = PIXEL (*data);
  (*data) += 2;
  P[2] = PIXEL (*data);
  (*data) += 2;
  P[3] = PIXEL (*data);
  (*data) += 2;

  for (y = 0; y < 8; ++y) {
    if (y < 4)
      index = 0;
    else
      index = 2;

    for (x = 0; x < 8; ++x) {
      if (x == 4)
        ++index;
      *frame++ = P[index];
    }
    frame += s->width - 8;
  }

  return 0;
}
