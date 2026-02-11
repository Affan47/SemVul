getHadronContent(tcPPtr hadron) const {
  HadronContent hc;
  hc.hadron = hadron->dataPtr();
  long id(hadron->id());

  if(BaryonMatcher::Check(hadron->data())) {
    hc.sign = id < 0? -1: 1;
    hc.flav.push_back((id = abs(id)/10)%10);
    hc.flav.push_back((id /= 10)%10);
    hc.flav.push_back((id /= 10)%10);
    hc.extracted = -1;
  }
  else if(hadron->data().id()==ParticleID::gamma ||
	  (hadron->data().id()==ParticleID::pomeron && pomeronStructure_==1)) {
    hc.sign = 1;
    for(int ix=1;ix<6;++ix) {
      hc.flav.push_back( ix);
      hc.flav.push_back(-ix);
    }
  }
  else if(hadron->data().id()==ParticleID::pomeron ) {
    hc.sign = 1;
    hc.flav.push_back(ParticleID::g);
    hc.flav.push_back(ParticleID::g);
  }
  else if(hadron->data().id()==ParticleID::reggeon ) {
    hc.sign = 1;
    for(int ix=1;ix<3;++ix) {
      hc.flav.push_back( ix);
      hc.flav.push_back(-ix);
    }
  }
  hc.pomeronStructure = pomeronStructure_;
  return hc;
}
