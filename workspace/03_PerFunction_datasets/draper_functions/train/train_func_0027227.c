decayMode(vector<int> idout) {
  unsigned int npi(0);
  for(unsigned int ix=0;ix<idout.size();++ix) {
    if(abs(idout[ix])==ParticleID::pi0) ++npi;
  }
  return npi/2;
}
