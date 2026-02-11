initProc() {


  nQuarkNew  = settingsPtr->mode("ExtraDimensionsLED:nQuarkNew");
  eDopMode   = settingsPtr->mode("ExtraDimensionsLED:opMode");
  eDnGrav    = settingsPtr->mode("ExtraDimensionsLED:n");
  eDMD       = settingsPtr->parm("ExtraDimensionsLED:MD");
  eDLambdaT  = settingsPtr->parm("ExtraDimensionsLED:LambdaT");
  eDnegInt   = settingsPtr->mode("ExtraDimensionsLED:NegInt");
  eDcutoff   = settingsPtr->mode("ExtraDimensionsLED:CutOffMode");
  eDtff      = settingsPtr->parm("ExtraDimensionsLED:t");

}
