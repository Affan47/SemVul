threeBodyMEIntegrator(const DecayMode & dm) const {

  int imode(-1);

  int id0(dm.parent()->id()),idf[2],ids(0);
  unsigned int nf(0);
  ParticleMSet::const_iterator pit = dm.products().begin();
  for( ;pit!=dm.products().end();++pit) {
    if((**pit).iSpin()==PDT::Spin0){ids=(**pit).id();}
    else{idf[nf]=(**pit).id();++nf;}
  }

  unsigned int ix=0;
  do {
    if(_incoming[ix]==id0&&_outgoingP[ix]==ids) {
      if((idf[0]==_outgoingf[ix]&&idf[1]==_outgoinga[ix])||
	 (idf[1]==_outgoingf[ix]&&idf[0]==_outgoinga[ix])) imode=ix;
    }
    ++ix;
  }
  while(imode<0&&ix<_incoming.size());

  Energy m[3]={getParticleData(_outgoingP[imode])->mass(),
	       getParticleData(_outgoingf[imode])->mass(),
	       getParticleData(_outgoinga[imode])->mass()};
  return
    new_ptr(ThreeBodyAllOn1IntegralCalculator<VectorMesonPScalarFermionsDecayer>
	    (3,-1000.*MeV,-0.8*MeV,-0.8,*this,imode,m[0],m[1],m[2]));
}
