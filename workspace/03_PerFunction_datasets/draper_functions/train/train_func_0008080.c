operator++() {
  plusplusIntern();

  if (mPos >= anz_pfade) {

    #if HAVE_LIBZ
      if (mAuch_gz)
        mDatei = mDatei + "[.gz]";
    #endif

    Str versuche = "";
    mPos = -1; plusplusIntern();
    do {
      versuche = versuche + "\n  " + pfad();
      plusplusIntern();
    } while (mPos<anz_pfade);

    throw Fehler(_("Could not find \"%s\".\nTried the following places:%s"),
		 mDatei.data(), versuche.data());
  }

  return *this;
}
