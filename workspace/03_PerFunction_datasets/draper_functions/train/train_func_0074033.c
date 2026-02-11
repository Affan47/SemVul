mode(string keyIn, int nowIn) {
  if (isMode(keyIn)) {
    string keyLower = toLower(keyIn);
    Mode& modeNow = modes[keyLower];
    if (modeNow.hasMin && nowIn < modeNow.valMin)
      modeNow.valNow = modeNow.valMin;
    else if (modeNow.hasMax && nowIn > modeNow.valMax)
      modeNow.valNow = modeNow.valMax;
    else modeNow.valNow = nowIn;

    if (keyLower == "tune:ee") initTuneEE( modeNow.valNow);
    if (keyLower == "tune:pp") initTunePP( modeNow.valNow);
  }
}
