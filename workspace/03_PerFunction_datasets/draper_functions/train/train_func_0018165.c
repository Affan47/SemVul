isinusfor(double lon, double lat, double *x, double *y)


{
  int istat;


  istat = Isin_fwd(isin, lon, lat, x, y);
  if (istat != ISIN_SUCCESS) {
    error("isinusfor", "bad return from Isin_fwd");
    return ISIN_ERROR;
  }

  return ISIN_SUCCESS;
}
