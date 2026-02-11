A(tcPDPtr lin, tcPDPtr,
			      tcPDPtr qin, tcPDPtr, Energy2 q2) const {

  if(_gammaZ==1) return 0.;

  double r = _gammaZ==0 || _gammaZ==2 ? double(q2/(q2+_mz2)) : 0.;
  double eL,eQ,cvL,caL,cvQ,caQ;;
  if(abs(lin->id())%2==0) {
    eL = _gammaZ==0 ? generator()->standardModel()->enu() : 0.;
    cvL = 0.25*generator()->standardModel()->vnu();
    caL = 0.25*generator()->standardModel()->anu();
  }
  else {
    eL = _gammaZ==0 ? generator()->standardModel()->ee()  : 0.;
    cvL = 0.25*generator()->standardModel()->ve();
    caL = 0.25*generator()->standardModel()->ae();
  }
  if(abs(qin->id())%2==0) {
    eQ = _gammaZ==0 ? generator()->standardModel()->eu() : 0.;
    cvQ = 0.25*generator()->standardModel()->vu();
    caQ = 0.25*generator()->standardModel()->au();
  }
  else {
    eQ = _gammaZ==0 ? generator()->standardModel()->ed() : 0.;
    cvQ = 0.25*generator()->standardModel()->vd();
    caQ = 0.25*generator()->standardModel()->ad();
  }
  double output = 4.*r*caL*caQ*(eL*eQ+2.*r*cvL*cvQ/sqr(_sinW*_cosW))
    /sqr(_sinW*_cosW)/(sqr(eL*eQ)+2.*eL*eQ*r/sqr(_cosW*_sinW)*cvL*cvQ
      +sqr(r/sqr(_cosW*_sinW))*(sqr(cvL)+sqr(caL))*(sqr(cvQ)+sqr(caQ)));
  if(qin->id()<0) output *= -1.;
  if(lin->id()<0) output *= -1.;
  return output;
}
