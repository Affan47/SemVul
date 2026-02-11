sigmaHat() {


  int idAbs     = (id2 == 22) ? abs(id1) : abs(id2);
  double charge = (idAbs > 10) ? 1. : ( (idAbs%2 == 1) ? 1./3. : 2./3. );
  double sigma  = sigma0 * pow2( charge  - sH / (sH + uH) );


  sigma        *= couplingsPtr->V2CKMsum(idAbs);
  int idUp      = (id2 == 22) ? id1 : id2;
  if (idAbs%2 == 1) idUp = -idUp;
  sigma        *= (idUp > 0) ? openFracPos : openFracNeg;


  return sigma;

}
