getCosTheta(double ctmin, double ctmax, const double r) {
  double cth = 0.0;
  double zmin = 0.5*(1.0 - ctmax);
  double zmax = 0.5*(1.0 - ctmin);
  if ( zmin <= 0.0 || zmax >= 1.0 ) {
    jacobian((ctmax - ctmin)*jacobian());
    cth = ctmin + r*(ctmax-ctmin);
  } else {
    double A1 = (2.0*zmax - 1.0)/(zmax*(1.0-zmax));
    double A0 = (2.0*zmin - 1.0)/(zmin*(1.0-zmin));
    double A = r*(A1 - A0) + A0;
    double z = A < 2.0? 2.0/(sqrt(sqr(A) + 4.0) + 2 - A):
      0.5*(A - 2.0 + sqrt(sqr(A) + 4.0))/A;
    cth = 1.0 - 2.0*z;
    jacobian((2.0*(A1 - A0)*sqr(z)*sqr(1.0 - z)/(sqr(z) + sqr(1.0 - z)))*jacobian());
  }
  return cth;
}
