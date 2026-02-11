generateNextSpaceBranching(const Energy startingQ,
			   const IdList &ids,
			   double x,bool cc,
			   double enhance,
			   Ptr<BeamParticleData>::transient_const_pointer beam) {


  q_ = ZERO;
  z(0.);
  phi(0.);

  Energy2 tmax(sqr(startingQ)),tmin;
  initialize(ids,tmin,cc);

  if(tmax<=tmin) return ShoKinPtr();


  tcPDPtr parton0 = getParticleData(ids[0]);
  tcPDPtr parton1 = getParticleData(ids[1]);
  if(cc) {
    if(parton0->CC()) parton0 = parton0->CC();
    if(parton1->CC()) parton1 = parton1->CC();
  }

  Energy2 t(tmax),pt2(ZERO);
  do {
    if(!guessSpaceLike(t,tmin,x,enhance)) break;
    pt2=sqr(1.-z())*t-z()*masssquared_[2];
  }
  while(z() > zLimits().second ||
	SplittingFnVeto((1.-z())*t/z(),ids,true) ||
	alphaSVeto(sqr(1.-z())*t) ||
	PDFVeto(t,x,parton0,parton1,beam) || pt2 < pT2min() );
  if(t > ZERO && zLimits().first < zLimits().second)  q_ = sqrt(t);
  else return ShoKinPtr();
  phi(Constants::twopi*UseRandom::rnd());
  pT(sqrt(pt2));

  return createInitialStateBranching(q_,z(),phi(),pT());
}
