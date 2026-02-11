normcdf(const RowVector& vals, const float mu, const float var)
{
  RowVector res(vals);
  RowVector tmp;
  tmp = (vals-mu)/std::sqrt(var);
  for (int mc=1; mc<=res.Ncols(); mc++){
    res(mc) = ndtr(tmp(mc));
  }

  res.Release();
  return res;
}
