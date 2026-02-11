can_scooch(struct imgcache_element *one,
                      struct imgcache_element *two)
{
  int i,x,y;

  if (!one)
    return 0;
  if (!two)
    return 0;

  if (one->posY != two->posY)
    return 0;
  if (one->height != two->height)
    return 0;
  if (one->posX + one->width != two->posX)
    return 0;


  i = 0;

  while (i < one->width && i < two->width) {
      i ++;
      for (y = 0; y < one->height; y++) {
          for (x = 0; x < i; x++ ) {
              int p1, p2;

              p1 = get_pixel(one, one->width - i + x,y);
              p2 = get_pixel(two, x, y);
              if ( p1 != p2)
                return i-1;
            }
        }
    }
  return i;
}
