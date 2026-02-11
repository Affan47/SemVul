doinit() {
  DrellYanBase::doinit();
  _wp=getParticleData(ThePEG::ParticleID::Wplus);
  _wm=getParticleData(ThePEG::ParticleID::Wminus);

  tcHwSMPtr hwsm=ThePEG::dynamic_ptr_cast<tcHwSMPtr>(standardModel());

  if(hwsm)
    _theFFWVertex = hwsm->vertexFFW();
  else
    throw InitException() << "Must be the Herwig++ StandardModel class in "
			  << "MEqq2W2ff::doinit" << Exception::abortnow;
}
