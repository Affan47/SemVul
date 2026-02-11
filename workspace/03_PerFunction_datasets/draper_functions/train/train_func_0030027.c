pickCosTheta(double Wcm) {

  int WcmBin = int((Wcm - mA - mB) / WCMBIN);
  if (WcmBin < 0) WcmBin = 0;
  if (WcmBin >= int(gridMax[subprocess].size()))
    WcmBin = int(gridMax[subprocess].size() - 1);


  double ct, wgt;

  do {

    double y   = rndmPtr->flat() * gridNorm[subprocess][WcmBin];
    double sum = 0.;
    int    ctBin;
    for (ctBin = 0; ctBin < int(2. / CTBIN); ctBin++) {
      if (sum + CTBIN * gridMax[subprocess][WcmBin][ctBin] > y) break;
      sum += CTBIN * gridMax[subprocess][WcmBin][ctBin];
    }


    double x1 = -1. + CTBIN * double(ctBin);
    double y1 = sum;
    double x2 = x1 + CTBIN;
    double y2 = sum + CTBIN * gridMax[subprocess][WcmBin][ctBin];
           ct = (x2 - x1) / (y2 - y1) * (y - y1) + x1;
    wgt = dSigma(Wcm, ct) / gridMax[subprocess][WcmBin][ctBin];
    if (wgt >= 1.) {
      infoPtr->errorMsg("Warning in SigmaPartialWave::pickCosTheta: "
        "weight above unity");
      break;
    }
  } while (wgt <= rndmPtr->flat());

  return ct;
}
