_tenAnisoTen_FA_d(const double tt[7]) {
  double denom, mn, stdv, dev[7];
  denom = 2.0*TEN_T_DOT(tt, tt);
  mn = TEN_T_TRACE(tt)/3;
  TEN_T_SET(dev, tt[0], tt[1]-mn, tt[2], tt[3], tt[4]-mn, tt[5], tt[6]-mn);
  stdv = TEN_T_DOT(dev, dev);
  return denom ? AIR_CAST(float, sqrt(3.0*stdv/denom)) : 0.0;
}
