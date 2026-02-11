convert_yuva4444(uint8_t ** dst, uint8_t ** src, int size)
  {
  int i;
  uint8_t *y, *u, *v, *a, *d;

  y = src[0];
  u = src[1];
  v = src[2];
  a = src[3];

  d = dst[0];

  for(i = 0; i < size; i++)
    {
    *(d++) = *(y++);
    *(d++) = *(u++);
    *(d++) = *(v++);
    *(d++) = y_8_to_yj_8[*(a++)];
    }
  }
