rotateZ(double delta) {
  double c1 = std::cos (delta);
  double s1 = std::sin (delta);
  HepLorentzVector rowx = row1();
  HepLorentzVector rowy = row2();
  HepLorentzVector r1 = c1 * rowx - s1 * rowy;
  HepLorentzVector r2 = s1 * rowx + c1 * rowy;
  mxx = r1.x();   mxy = r1.y();   mxz = r1.z();   mxt = r1.t();
  myx = r2.x();   myy = r2.y();   myz = r2.z();   myt = r2.t();
  return *this;
}
