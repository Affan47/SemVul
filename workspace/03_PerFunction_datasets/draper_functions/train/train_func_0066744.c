me2(const int, const Particle & inpart,
				       const ParticleVector & decay,
				       MEOption meopt) const {

  if(meopt==Initialize) {
    _rho = RhoDMatrix(PDT::Spin2);
    TensorWaveFunction::
      calculateWaveFunctions(_tensors,_rho,const_ptr_cast<tPPtr>(&inpart),
			     incoming,false);
  }
  if(meopt==Terminate) {
    TensorWaveFunction::constructSpinInfo(_tensors,const_ptr_cast<tPPtr>(&inpart),
					  incoming,true,false);

    for(unsigned int ix=0;ix<decay.size();++ix)
      ScalarWaveFunction::constructSpinInfo(decay[ix],outgoing,true);
    return 0.;
  }

  for(unsigned int ix=0;ix<5;++ix) {
    ME()(ix,0,0) = _coupling[imode()]/inpart.mass()*
      ((_tensors[ix]*decay[1]->momentum())*decay[0]->momentum());
  }


  return ME().contract(_rho).real();
}
