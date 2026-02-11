me2(const int , const Particle & inpart,
		       const ParticleVector & decay,
		       MEOption meopt) const {
  unsigned int isc(0),ivec(1);
  if(decay[0]->dataPtr()->iSpin() != PDT::Spin0) swap(isc,ivec);
  if(meopt==Initialize) {
    ScalarWaveFunction::
      calculateWaveFunctions(_rho,const_ptr_cast<tPPtr>(&inpart),incoming);
    _swave = ScalarWaveFunction(inpart.momentum(),inpart.dataPtr(),incoming);
    if(ivec==1)
      ME(DecayMatrixElement(PDT::Spin0,PDT::Spin0,PDT::Spin1));
    else
      ME(DecayMatrixElement(PDT::Spin0,PDT::Spin1,PDT::Spin0));
  }
  if(meopt==Terminate) {
    ScalarWaveFunction::
      constructSpinInfo(const_ptr_cast<tPPtr>(&inpart),incoming,true);
    ScalarWaveFunction::
      constructSpinInfo(decay[isc],outgoing,true);
    VectorWaveFunction::
      constructSpinInfo(_vector,decay[ivec],outgoing,true,false);
  }
  VectorWaveFunction::
    calculateWaveFunctions(_vector,decay[ivec],outgoing,false);
  ScalarWaveFunction sca(decay[isc]->momentum(),decay[isc]->dataPtr(),outgoing);
  Energy2 scale(sqr(inpart.mass()));

  double output(0.);
  if(ivec == 0) {
    for(unsigned int ix = 0; ix < 3; ++ix)
      ME()(0, ix, 0) = _abstractVertex->evaluate(scale,_vector[ix],sca, _swave);
  }
  else {
    for(unsigned int ix = 0; ix < 3; ++ix)
      ME()(0, 0, ix) = _abstractVertex->evaluate(scale,_vector[ix],sca,_swave);
  }
  output = (ME().contract(_rho)).real()/scale*UnitRemoval::E2;

  output *= colourFactor(inpart.dataPtr(),decay[0]->dataPtr(),
			 decay[1]->dataPtr());

  return output;
}
