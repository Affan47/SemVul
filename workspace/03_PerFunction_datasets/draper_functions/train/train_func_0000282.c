pixel_fogofwar_hexa(const struct tile *ptile,
                                    const struct player *pplayer,
                                    bool knowledge)
{
  bv_pixel pixel;

  BV_CLR_ALL(pixel);
  BV_SET(pixel,  0);
  BV_SET(pixel,  3);
  BV_SET(pixel,  5);
  BV_SET(pixel,  7);
  BV_SET(pixel,  9);
  BV_SET(pixel, 11);
  BV_SET(pixel, 13);
  BV_SET(pixel, 15);
  BV_SET(pixel, 17);
  BV_SET(pixel, 18);
  BV_SET(pixel, 20);
  BV_SET(pixel, 22);
  BV_SET(pixel, 24);
  BV_SET(pixel, 26);
  BV_SET(pixel, 28);
  BV_SET(pixel, 30);
  BV_SET(pixel, 32);
  BV_SET(pixel, 35);

  return pixel;
}
