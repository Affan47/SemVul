initProc() {


  if (eDgraviton) {
    eDspin     = 2;
    eDnGrav    = settingsPtr->mode("ExtraDimensionsLED:n");
    eDdU       = 2;
    eDLambdaU  = settingsPtr->parm("ExtraDimensionsLED:LambdaT");
    eDlambda   = 1;
    eDnegInt   = settingsPtr->mode("ExtraDimensionsLED:NegInt");
    eDcutoff   = settingsPtr->mode("ExtraDimensionsLED:CutOffMode");
    eDtff      = settingsPtr->parm("ExtraDimensionsLED:t");
  } else {
    eDspin     = settingsPtr->mode("ExtraDimensionsUnpart:spinU");
    eDdU       = settingsPtr->parm("ExtraDimensionsUnpart:dU");
    eDLambdaU  = settingsPtr->parm("ExtraDimensionsUnpart:LambdaU");
    eDlambda   = settingsPtr->parm("ExtraDimensionsUnpart:lambda");
    eDnegInt   = 0;
  }


  if (eDgraviton) {
    eDlambda2chi = 4*M_PI;
    if (eDnegInt == 1) eDlambda2chi *= -1.;
  } else {
    double tmPAdU = 16 * pow2(M_PI) * sqrt(M_PI) / pow(2. * M_PI, 2. * eDdU)
      * GammaReal(eDdU + 0.5) / (GammaReal(eDdU - 1.) * GammaReal(2. * eDdU));
    double tmPdUpi = eDdU * M_PI;
    eDlambda2chi = pow2(eDlambda) * tmPAdU / (2 * sin(tmPdUpi));
  }


  if ( !(eDspin==0 || eDspin==2) ) {
    eDlambda2chi = 0;
    infoPtr->errorMsg("Error in Sigma2ffbar2LEDgammagamma::initProc: "
		      "Incorrect spin value (turn process off)!");
  } else if ( !eDgraviton && (eDdU >= 2)) {
    eDlambda2chi = 0;
    infoPtr->errorMsg("Error in Sigma2ffbar2LEDgammagamma::initProc: "
		      "This process requires dU < 2 (turn process off)!");
  }

}
