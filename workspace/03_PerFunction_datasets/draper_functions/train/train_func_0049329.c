parm(string keyIn) {
  if (isParm(keyIn)) return parms[toLower(keyIn)].valNow;
  infoPtr->errorMsg("Error in Settings::parm: unknown key", keyIn);
  return 0.;
}
