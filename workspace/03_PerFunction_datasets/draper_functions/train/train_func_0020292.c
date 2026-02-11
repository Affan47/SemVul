rank_closest_op_real(float* value, int count, int center)
{
  float v = value[center];
  float min, max;

  imMinMax(value, count, min, max);

  if (v - min < max - v)
    return min;
  else
    return max;
}
