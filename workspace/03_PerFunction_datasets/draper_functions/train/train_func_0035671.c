compute_red(int w, int h, int rw, int rh)
{
  for (int red=1; red<16; red++)
    if (((w+red-1)/red==rw) && ((h+red-1)/red==rh))
      return red;
  return 16;
}
