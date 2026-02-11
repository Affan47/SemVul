me2(const int,
					    const Particle & inpart,
					    const ParticleVector & decay,
					    MEOption meopt) const {

  bool photon(_outgoingV[imode()]==ParticleID::gamma);
  if(meopt==Initialize) {
    VectorWaveFunction::calculateWaveFunctions(_vectors[0],_rho,
					       const_ptr_cast<tPPtr>(&inpart),
					       incoming,false);
  }
  if(meopt==Terminate) {
    VectorWaveFunction::constructSpinInfo(_vectors[0],const_ptr_cast<tPPtr>(&inpart),
					  incoming,true,false);
    VectorWaveFunction::constructSpinInfo(_vectors[1],decay[0],
					  outgoing,true,photon);
    ScalarWaveFunction::constructSpinInfo(decay[1],outgoing,true);
    return 0.;
  }
  VectorWaveFunction::calculateWaveFunctions(_vectors[1],decay[0],outgoing,photon);

  LorentzPolarizationVector vtemp;
  for(unsigned int ix=0;ix<3;++ix) {
    if(ix==1&&photon) {
      for(unsigned int iy=0;iy<3;++iy) ME()(iy,ix,0)=0.;
    }
    else {
      vtemp=_coupling[imode()]/inpart.mass()*
	epsilon(inpart.momentum(),_vectors[1][ix],decay[0]->momentum());
      for(unsigned int iy=0;iy<3;++iy) ME()(iy,ix,0)=_vectors[0][iy].dot(vtemp);
    }
  }


  return ME().contract(_rho).real();
}
