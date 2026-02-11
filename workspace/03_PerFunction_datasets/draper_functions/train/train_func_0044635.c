doinit() {
  HwMEBase::doinit();
  _z0    = getParticleData(ThePEG::ParticleID::Z0   );
  _gamma = getParticleData(ThePEG::ParticleID::gamma);

  ThePEG::Ptr<Herwig::StandardModel>::transient_const_pointer
    hwsm=ThePEG::dynamic_ptr_cast< ThePEG::Ptr<Herwig::StandardModel>
    ::transient_const_pointer>(standardModel());

  if(!hwsm)
    throw InitException() << "Must be Herwig::StandardModel in MEPP2ZJet::doinit()"
			  << Exception::runerror;

  _theFFZVertex = hwsm->vertexFFZ();
  _theFFPVertex = hwsm->vertexFFP();
  _theQQGVertex = hwsm->vertexFFG();
}
