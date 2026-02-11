boostMomenta(const Boost & boostv) {

  Energy L0(_bigLdrf.e()),modL(_bigLdrf.rho());

  Energy modq(_qdrf[0].rho());

  Energy newE12(-L0+sqrt(_m[0]*_m[0]+modL*modL));

  if(newE12<_m[1]+_m[2]){return false;}

  double kappa(Kinematics::pstarTwoBodyDecay(newE12,_m[1],_m[2])/modq);

  for(unsigned int ix=0;ix<2;++ix) {
    _qnewdrf[ix] = kappa*_qdrf[ix];
    _qnewdrf[ix].setMass(_m[ix+1]);
    _qnewdrf[ix].rescaleEnergy();
  }

  Lorentz5Momentum pnew(_bigLdrf.x(),_bigLdrf.y(),
			_bigLdrf.z(),_bigLdrf.e(),_m[0]);
  pnew.rescaleEnergy();


  SpinOneLorentzRotation boost(pnew.findBoostToCM());

  for(unsigned int ix=0;ix<2;++ix) _qnewprf[ix]=boost*_qnewdrf[ix];

  _bigLprf=boost*_bigLdrf;

  for(unsigned int ix=0;ix<_multiplicity;++ix){_lprf[ix]=boost*_ldrf[ix];}

  boost.setBoost(boostv);

  for(unsigned int ix=0;ix<2;++ix){_qnewlab[ix]=boost*_qnewprf[ix];}

  _bigLlab=boost*_bigLprf;

  for(unsigned int ix=0;ix<_multiplicity;++ix){_llab[ix]=boost*_lprf[ix];}
  return true;
}
