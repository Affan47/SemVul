EvaluateSet(double p[4])
{
  unsigned short count = 0;
  double v0, v1;
  double cReal, cImag, zReal, zImag;
  double zReal2, zImag2;

  cReal = p[0];
  cImag = p[1];
  zReal = p[2];
  zImag = p[3];

  zReal2 = zReal * zReal;
  zImag2 = zImag * zImag;
  v0 = 0.0;
  v1 = (zReal2 + zImag2);
  while ( v1 < 4.0 && count < this->MaximumNumberOfIterations)
    {
    zImag = 2.0 * zReal * zImag + cImag;
    zReal = zReal2 - zImag2 + cReal;
    zReal2 = zReal * zReal;
    zImag2 = zImag * zImag;
    ++count;
    v0 = v1;
    v1 = (zReal2 + zImag2);
    }

  if (count == this->MaximumNumberOfIterations)
    {
    return static_cast<float>(count);
    }

  return static_cast<float>(count) + static_cast<float>((4.0 - v0)/(v1 - v0));
}
