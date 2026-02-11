circleSize(const SbVec3f &a, const SbVec3f &b, const SbVec3f &c)
{
  tessfloat_t cx, cy;
  if (circleCenter(a, b, c, cx, cy)) {
    tessfloat_t t1, t2;
    t1 = a[X] - cx;
    t2 = a[Y] - cy;
    return t1*t1+t2*t2;
  }
  return FLT_MAX;
}
