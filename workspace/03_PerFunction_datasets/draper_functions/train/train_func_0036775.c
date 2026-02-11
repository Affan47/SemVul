pone (double x)
{
  const double *p, *q;
  double z, r, s, r1, r2, r3, s1, s2, s3, z2, z4;
  int32_t ix;
  GET_HIGH_WORD (ix, x);
  ix &= 0x7fffffff;
  if (ix >= 0x41b00000)
    {
      return one;
    }
  else if (ix >= 0x40200000)
    {
      p = pr8; q = ps8;
    }
  else if (ix >= 0x40122E8B)
    {
      p = pr5; q = ps5;
    }
  else if (ix >= 0x4006DB6D)
    {
      p = pr3; q = ps3;
    }
  else if (ix >= 0x40000000)
    {
      p = pr2; q = ps2;
    }
  z = one / (x * x);
  r1 = p[0] + z * p[1]; z2 = z * z;
  r2 = p[2] + z * p[3]; z4 = z2 * z2;
  r3 = p[4] + z * p[5];
  r = r1 + z2 * r2 + z4 * r3;
  s1 = one + z * q[0];
  s2 = q[1] + z * q[2];
  s3 = q[3] + z * q[4];
  s = s1 + z2 * s2 + z4 * s3;
  return one + r / s;
}
