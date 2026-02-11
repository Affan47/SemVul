ho_array_stat_init (ho_array_stat * ar, const ho_array * pix)
{
  double value;

  double value2;

  int x, y;


  for (x = 0; x < pix->width; x++)
    for (y = 0; y < pix->height; y++)
    {
      value = ho_array_get (pix, x, y);
      value2 = square (value);

      ho_array_stat_set_sum (ar, x, y, value);
      ho_array_stat_set_sqr_sum (ar, x, y, value2);
    }


  ar->size = 1;

  return FALSE;
}
