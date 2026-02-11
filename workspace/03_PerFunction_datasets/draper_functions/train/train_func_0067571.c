iColorNormHue(double H)
{
  while (H < 0.0)
    H += rad360;

  if (H > rad360)
    H = fmod(H, (double)rad360);

  return H;
}
