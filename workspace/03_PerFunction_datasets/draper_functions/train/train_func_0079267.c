speichereBildFremd(Ort & ort, int ebene) {
  CASSERT(mDaten);

  ort_absolut ziel = ort.berechne(mOrt,*this);
  if (ziel.korrekt()) {
    Blop & b = ziel.finde();

    if ((!mMalenErlaubt) || (!b.mOrt.bemalbar()))
      throw Fehler("%s",_("Drawing is not allowed at the moment."));


    b.braucheInitStapel();

    b.mBild.speichereBild(
          getSorte(), mDaten[spezvar_file], mDaten[spezvar_pos],
          mDaten[spezvar_quarter], ebene);
  }
}
