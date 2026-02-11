switch_func(double t)
{
  if (sf == 2) return l_initial / (1 + t * (l_initial/l_final - 1));
  if (sf == 3) return l_initial / (1 + log2(1+t) * (l_initial/l_final - 1));


  return l_initial + (l_final - l_initial) * t;
}
