decayWeightMax(vector<HelicityParticle>& p) {


  double on  = real(p[0].rho[0][0]) > real(p[0].rho[1][1]) ?
    real(p[0].rho[0][0]) : real(p[0].rho[1][1]);

  double off = fabs(real(p[0].rho[0][1])) + fabs(imag(p[0].rho[0][1]));
  return  DECAYWEIGHTMAX * (on + off);

}
