colourGeometries(tcDiagPtr diag) const {

  static const ColourLines qqbar1("1 5, -5 -2 -3");
  static const ColourLines qqbar2("1 2 5, -5 -3");

  static const ColourLines qg1("1 2 -3, 3 5");
  static const ColourLines qg2("1 -2, 2 3 5");

  static const ColourLines qbarg1("-1 -2 3, -3 -5");
  static const ColourLines qbarg2("-1 2, -2 -3 -5");

  Selector<const ColourLines *> sel;
  switch (diag->id()) {
  case -1 :
    sel.insert(1.0, &qqbar1);
    break;
  case -2 :
    sel.insert(1.0, &qqbar2);
    break;
  case -3 :
    sel.insert(1.0, &qg1);
    break;
  case -4 :
    sel.insert(1.0, &qg2);
    break;
  case -5 :
    sel.insert(1.0, &qbarg1);
    break;
  case -6 :
    sel.insert(1.0, &qbarg2);
    break;
  }
  return sel;
}
