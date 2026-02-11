calcPreFac(bool calledFromInit) {


  alpS          = couplingsPtr->alphaS(mHat * mHat);
  preFac        = alpS * mHat / 6;


  if (!calledFromInit) {

    int idInFlavAbs = abs(idInFlav);
    double sH = mHat * mHat;
    normSM   = 1;
    normInt  = 2. * eDgv[min(idInFlavAbs, 9)] * sH * (sH - m2Res)
              / ( pow2(sH - m2Res) + pow2(sH * GamMRat) );
    normKK   = ( pow2(eDgv[min(idInFlavAbs, 9)])
	       + pow2(eDga[min(idInFlavAbs, 9)]) ) * sH * sH
              / ( pow2(sH - m2Res) + pow2(sH * GamMRat) );


    if (interfMode == 1) {normInt = 0.; normKK = 0.;}
    if (interfMode == 2) {normSM = 0.; normInt = 0.; normKK = 1.;}
  }

}
