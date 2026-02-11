yquant (double y, unsigned int Yres, int dir)
{
  double tmp;
  unsigned int t;

  tmp = (double) y *Yres;
  t = (unsigned int) tmp;

  if (tmp - ((double) t) >= 0.1)
    if (dir)
      t++;;

  return t * 1200 / Yres;
}
