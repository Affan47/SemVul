me2(const int , const Particle & inpart,
		       const ParticleVector & decay,
		       MEOption meopt) const {
  if(meopt==Initialize) {
    TensorWaveFunction::
      calculateWaveFunctions(_tensors,_rho,const_ptr_cast<tPPtr>(&inpart),
			     incoming,false);
    ME(DecayMatrixElement(PDT::Spin2,PDT::Spin0,PDT::Spin0));
  }
  if(meopt==Terminate) {
    TensorWaveFunction::
      constructSpinInfo(_tensors,const_ptr_cast<tPPtr>(&inpart),
			incoming,true,false);
    for(unsigned int ix=0;ix<2;++ix)
      ScalarWaveFunction::
	constructSpinInfo(decay[ix],outgoing,true);
    return 0.;
  }
  ScalarWaveFunction sca1(decay[0]->momentum(),decay[0]->dataPtr(),outgoing);
  ScalarWaveFunction sca2(decay[1]->momentum(),decay[1]->dataPtr(),outgoing);
  Energy2 scale(sqr(inpart.mass()));
  for(unsigned int thel=0;thel<5;++thel) {
    ME()(thel,0,0) =_abstractVertex->evaluate(scale,sca1,sca2,_tensors[thel]);
  }
  double output = (ME().contract(_rho)).real()/scale*UnitRemoval::E2;

  output *= colourFactor(inpart.dataPtr(),decay[0]->dataPtr(),
			 decay[1]->dataPtr());

  return output;
}
