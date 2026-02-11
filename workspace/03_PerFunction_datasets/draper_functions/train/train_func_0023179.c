gcgeodist(const double lat1, const double lon1,
          const double lat2, const double lon2)
{
  double res;

  res = radtometers(gcdist(RAD(lat1), RAD(lon1), RAD(lat2), RAD(lon2)));
  if (res < 0.1) {
    res = 0;
  }

  return res;
}
