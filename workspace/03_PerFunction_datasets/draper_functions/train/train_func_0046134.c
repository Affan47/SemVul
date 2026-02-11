resWidth(int idSgn, double mHat, int idIn,
  bool openOnly, bool setBR) {
  return (resonancePtr != 0) ? resonancePtr->width( idSgn, mHat,
    idIn, openOnly, setBR) : 0.;
}
