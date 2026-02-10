calcMEcorr(int MEtype, int idMother, int idDaughterIn,
  double M2, double z, double Q2) {


  double sH = M2 / z;
  double tH = -Q2;
  double uH = Q2 - M2 * (1. - z) / z;
  int idMabs = abs(idMother);
  int idDabs = abs(idDaughterIn);


  if (MEtype == 1) {
    if (idMabs < 20 && idDabs < 20) {
      return (tH*tH + uH*uH + 2. * M2 * sH) / (sH*sH + M2*M2);
    } else if (idDabs < 20) {


      swap( tH, uH);
      return (sH*sH + uH*uH + 2. * M2 * tH) / (pow2(sH - M2) + M2*M2);
    }


  } else if (MEtype == 2) {
    if (idMabs < 20 && idDabs > 20) {
      return (sH*sH + uH*uH) / (sH*sH + pow2(sH - M2));
    } else if (idDabs > 20) {
      return 0.5 * (pow4(sH) + pow4(tH) + pow4(uH) + pow4(M2))
        / pow2(sH*sH - M2 * (sH - M2));
    }


  } else if (MEtype == 3) {
    if (idMabs < 20 && idDabs < 20) {

      return 1.;
    } else if (idDabs < 20) {

      swap( tH, uH);
      return (sH*sH + uH*uH + 2. * (M2 - uH) * (M2 - sH))
             / (pow2(sH - M2) + M2*M2);
    }
  }

  return 1.;

}
