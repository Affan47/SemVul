finalKin() {


  for (int i = 0; i < 6; ++i) mH[i] = 0.;


  pH[1] = 0.5 * (pInSum.e() + pInSum.pz()) * Vec4( 0., 0.,  1., 1.);
  pH[2] = 0.5 * (pInSum.e() - pInSum.pz()) * Vec4( 0., 0., -1., 1.);


  tH    = 0.;
  uH    = 0.;
  pTH = (pH[3].pT() + pH[4].pT() + pH[5].pT()) / 3.;
  theta = 0.;
  phi   = 0.;

  return true;
}
