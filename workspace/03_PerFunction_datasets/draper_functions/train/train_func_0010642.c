initKinematics() {


  mA       = particleData.m0(idA);
  mB       = particleData.m0(idB);
  betaZ    = 0.;
  gammaZ   = 1.;


  if (boostType == 2) {
    eA     = max(eA, mA);
    eB     = max(eB, mB);
    pzA    = sqrt(eA*eA - mA*mA);
    pzB    = -sqrt(eB*eB - mB*mB);
    pAinit = Vec4( 0., 0., pzA, eA);
    pBinit = Vec4( 0., 0., pzB, eB);
    eCM    = sqrt( pow2(eA + eB) - pow2(pzA + pzB) );


    betaZ  = (pzA + pzB) / (eA + eB);
    gammaZ = (eA + eB) / eCM;
    if (abs(betaZ) < 1e-10) boostType = 1;
  }


  else if (boostType == 3) {
    eA     = sqrt( pxA*pxA + pyA*pyA + pzA*pzA + mA*mA);
    eB     = sqrt( pxB*pxB + pyB*pyB + pzB*pzB + mB*mB);
    pAinit = Vec4( pxA, pyA, pzA, eA);
    pBinit = Vec4( pxB, pyB, pzB, eB);
    eCM = (pAinit + pBinit).mCalc();


    MfromCM.reset();
    MfromCM.fromCMframe( pAinit, pBinit);
    MtoCM = MfromCM;
    MtoCM.invert();
  }


  if (eCM < mA + mB) {
    info.errorMsg("Error in Pythia::initKinematics: too low energy");
    return false;
  }


  pzAcm    = 0.5 * sqrtpos( (eCM + mA + mB) * (eCM - mA - mB)
           * (eCM - mA + mB) * (eCM + mA - mB) ) / eCM;
  pzBcm    = -pzAcm;
  eA       = sqrt(mA*mA + pzAcm*pzAcm);
  eB       = sqrt(mB*mB + pzBcm*pzBcm);


  if (boostType != 2 && boostType != 3) {
    pAinit = Vec4( 0., 0., pzAcm, eA);
    pBinit = Vec4( 0., 0., pzBcm, eB);
  }


  info.setBeamA( idA, pzAcm, eA, mA);
  info.setBeamB( idB, pzBcm, eB, mB);
  info.setECM( eCM);


  if (doMomentumSpread) boostType = 3;


  return true;

}
