initProc() {


  if (settingsPtr->flag("HiddenValley:doKinMix"))
    eQHV2      = pow2(settingsPtr->parm("HiddenValley:kinMix"));
  else
    eQHV2      = pow2( particleDataPtr->charge(idNew) );
  nCHV         = settingsPtr->mode("HiddenValley:Ngauge");
  kappa        = settingsPtr->parm("HiddenValley:kappa");


  hasColour    = (particleDataPtr->colType(idNew) != 0);
  colFac       = (hasColour) ? 3. : 1.;


  openFracPair = particleDataPtr->resOpenFrac(idNew, -idNew);

}
