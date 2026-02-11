draw_radar_frame (a_pixel *dest)
{
  unsigned int y;


  memset (dest, 15, 75);
  dest += xbuf;

  for (y = 40; y != 0; --y) {
    *dest = 15;
    dest[74] = 15;
    dest += xbuf;
  }

  memset (dest, 15, 75);
}
