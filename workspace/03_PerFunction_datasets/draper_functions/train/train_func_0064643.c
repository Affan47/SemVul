gaussianSkewNormal ( HepRandomEngine* e, double k)
{


  double u[2] = {0.};
  RandGaussT::shootArray(e, 2, u, 0, 1);
  double delta = k/std::sqrt(1. + k*k);
  double u1 = delta*u[0] + std::sqrt(1 - delta*delta)*u[1];
  double r = u[0] >= 0 ? u1 : -u1;
  return r;
}
