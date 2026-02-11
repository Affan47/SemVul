me2() const {

  VBVector v1(2), v2(2);
  SpinorVector sp(2); SpinorBarVector sbar(2);
  for( size_t i = 0; i < 2; ++i ) {
    v1[i] = VectorWaveFunction(rescaledMomenta()[0],mePartonData()[0], 2*i,
			       incoming);
    v2[i] = VectorWaveFunction(rescaledMomenta()[1],mePartonData()[1], 2*i,
			       incoming);
    sbar[i] = SpinorBarWaveFunction(rescaledMomenta()[2], mePartonData()[2], i,
				    outgoing);
    sp[i] = SpinorWaveFunction(rescaledMomenta()[3], mePartonData()[3], i,
			       outgoing);
  }
  double full_me(0.);
  vv2ffME(v1, v2, sbar, sp, full_me,true);

#ifndef NDEBUG
  if( debugME() ) debug(full_me);
#endif

  return full_me;
}
