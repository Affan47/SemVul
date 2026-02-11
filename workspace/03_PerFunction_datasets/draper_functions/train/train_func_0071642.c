airBesselIn(int nn, double xx) {
  double tax, bb, bi, bim, bip;
  int ii, an, top;

  an = AIR_ABS(nn);
  if (0 == an) {
    return airBesselI0(xx);
  } else if (1 == an) {
    return airBesselI1(xx);
  }

  if (0.0 == xx) {
    return 0.0;
  }

  tax = 2.0/AIR_ABS(xx);
  bip = bb = 0.0;
  bi = 1.0;
  top = 2*(an + AIR_CAST(int, sqrt(40.0*an)));
  for (ii=top; ii > 0; ii--) {
    bim = bip + ii*tax*bi;
    bip = bi;
    bi = bim;
    if (AIR_ABS(bi) > 1.0e10) {
      bb *= 1.0e-10;
      bi *= 1.0e-10;
      bip*= 1.0e-10;
    }
    if (ii == an) {
      bb = bip;
    }
  }
  bb *= airBesselI0(xx)/bi;
  return (xx < 0.0 ? -bb : bb);
}
