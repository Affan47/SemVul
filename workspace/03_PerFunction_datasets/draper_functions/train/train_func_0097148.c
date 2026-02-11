do_box(int x, int y, int, float* param)
{
  int xr = x - (int)param[3];
  int yr = y - (int)param[4];
  if (xr < -(int)param[1] || xr > (int)param[1] ||
      yr < -(int)param[2] || yr > (int)param[2])
    return 0;
  else
    return param[0];
}
