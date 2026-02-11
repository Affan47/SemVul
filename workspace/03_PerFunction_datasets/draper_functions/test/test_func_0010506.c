calculateFinalFinalScales(const ShowerPPair &particlePair) {
  static const double eps=1e-8;


  Lorentz5Momentum p1= particlePair.first->momentum();
  Lorentz5Momentum p2 = particlePair.second->momentum();
  Lorentz5Momentum p12(p1+p2);
  Boost boostv=p12.findBoostToCM();
  p1.boost(boostv);
  p2.boost(boostv);

  Energy2 Q2 = p12.m2();
  double b = p1.mass2()/Q2;
  double c = p2.mass2()/Q2;
  if(b<0.) {
    if(b<-eps) throw Exception() << "Negative Mass sqaured b = " << b
				 << "in QTildeFinder::calculateFinalFinalScales()"
				 << Exception::eventerror;
    b = 0.;
  }
  if(c<0.) {
    if(c<-eps) throw Exception() << "Negative Mass sqaured c = " << c
				 << "in QTildeFinder::calculateFinalFinalScales()"
				 << Exception::eventerror;
    c = 0.;
  }


  double lam=sqrt((1.+sqrt(b)+sqrt(c))*(1.-sqrt(b)-sqrt(c))
                 *(sqrt(b)-1.-sqrt(c))*(sqrt(c)-1.-sqrt(b)));

  unsigned int iopt=finalFinalConditions();
  Energy firstQ,secondQ;
  if(iopt==0) {
    firstQ  = sqrt(0.5*Q2*(1.+b-c+lam));
    secondQ = sqrt(0.5*Q2*(1.-b+c+lam));
  }

  else {
    double kappab,kappac;

    bool colouredFirst=particlePair.first->colourLine()&&
      particlePair.first->colourLine()==particlePair.second->antiColourLine();

    if((iopt==1&&colouredFirst)||
       (iopt==2&&!colouredFirst)||
       (iopt==3&&UseRandom::rndbool(0.5))) {
      kappab=4.*(1.-2.*sqrt(c)-b+c);
      kappac=c+0.25*sqr(1.-b-c+lam)/(kappab-b);
    }
    else {
      kappac=4.*(1.-2.*sqrt(b)-c+b);
      kappab=b+0.25*sqr(1.-b-c+lam)/(kappac-c);
    }

    firstQ  = sqrt(Q2*kappab);
    secondQ = sqrt(Q2*kappac);
  }
  return pair<Energy,Energy>(firstQ, secondQ);
}
