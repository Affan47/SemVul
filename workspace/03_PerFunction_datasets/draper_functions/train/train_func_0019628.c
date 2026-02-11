StringToFilterTypes(const char *option)
{
  FilterTypes
    filter = UndefinedFilter;

  if (LocaleCompare("Point",option) == 0)
    filter=PointFilter;
  else if (LocaleCompare("Box",option) == 0)
    filter=BoxFilter;
  else if (LocaleCompare("Triangle",option) == 0)
    filter=TriangleFilter;
  else if (LocaleCompare("Hermite",option) == 0)
    filter=HermiteFilter;
  else if (LocaleCompare("Hanning",option) == 0)
    filter=HanningFilter;
  else if (LocaleCompare("Hamming",option) == 0)
    filter=HammingFilter;
  else if (LocaleCompare("Blackman",option) == 0)
    filter=BlackmanFilter;
  else if (LocaleCompare("Gaussian",option) == 0)
    filter=GaussianFilter;
  else if (LocaleCompare("Quadratic",option) == 0)
    filter=QuadraticFilter;
  else if (LocaleCompare("Cubic",option) == 0)
    filter=CubicFilter;
  else if (LocaleCompare("Catrom",option) == 0)
    filter=CatromFilter;
  else if (LocaleCompare("Mitchell",option) == 0)
    filter=MitchellFilter;
  else if (LocaleCompare("Lanczos",option) == 0)
    filter=LanczosFilter;
  else if (LocaleCompare("Bessel",option) == 0)
    filter=BesselFilter;
  else if (LocaleCompare("Sinc",option) == 0)
    filter=SincFilter;

  return filter;
}
