forceMode(string keyIn, int nowIn) {
  if (isMode(keyIn)) {
    string keyLower = toLower(keyIn);
    Mode& modeNow   = modes[keyLower];
    modeNow.valNow  = nowIn;

    if (keyLower == "tune:ee") initTuneEE( modeNow.valNow);
    if (keyLower == "tune:pp") initTunePP( modeNow.valNow);
  }
}
