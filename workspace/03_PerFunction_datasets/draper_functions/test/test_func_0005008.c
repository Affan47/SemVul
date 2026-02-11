doinit() {
  HwMEBase::doinit();

  _Z0=getParticleData(ThePEG::ParticleID::Z0);
  _gamma=getParticleData(ThePEG::ParticleID::gamma);

  tcHwSMPtr hwsm= dynamic_ptr_cast<tcHwSMPtr>(standardModel());

  if(hwsm) {
    _theFFZVertex = hwsm->vertexFFZ();
    _theFFPVertex = hwsm->vertexFFP();
  }
  else {
    throw InitException() << "Wrong type of StandardModel object in "
			  << "MEee2gZ2ll::doinit() the Herwig++ version must be used"
			  << Exception::runerror;
  }
}
