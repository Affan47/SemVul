bonusSchritt() {

  CASSERT(mModus != modus_keinspiel);


  int unten = gric * gry - ld->mHetzrandStop;


  int ny = mHetzrandYPix + bonus_geschwindigkeit;
  if (ny > unten) ny = unten;

  setHetzrandYPix(ny);


  return ny == unten;
}
