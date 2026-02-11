getY(int a, int hv) const {
  int y0 = yy + gric - 1 + hv;

  if (ld->mSechseck && (getX(a) & 1))
    y0 += gric / 2;

  return y0 / gric + a * (r == richtung_senk);
}
