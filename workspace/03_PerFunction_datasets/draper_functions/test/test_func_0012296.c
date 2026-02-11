frame_dashed (int x, int y, int xd, int yd, a_pixel col1, a_pixel col2)
{
  int i;
  a_pixel *dest = hedit_buffer + y * xbuf + x;
  for (i = (xd >> 1); i > 0; i--) {
    dest[(yd - 1) * xbuf] = col1;
    *dest++ = col2;
    dest[(yd - 1) * xbuf] = col2;
    *dest++ = col1;
  };
  xd--;
  dest--;
  for (i = (yd >> 1); i > 0; i--) {
    dest[-xd] = col2;
    *dest = col1;
    dest += xbuf;
    dest[-xd] = col1;
    *dest = col2;
    dest += xbuf;
  };
}
