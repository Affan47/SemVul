doinit() {
  Baryon1MesonDecayerBase::doinit();

  setupModes(1);

  tPDVector extpart(3);
  DecayPhaseSpaceModePtr mode;
  double wgtmax;
  vector<double> wgt(0);
  for(unsigned int ix=0;ix<_outgoingB.size();++ix) {
    extpart[0]=getParticleData(_elambda);
    extpart[1]=getParticleData(_outgoingB[ix]);
    extpart[2]=getParticleData(_outgoingM[ix]);
    mode=new_ptr(DecayPhaseSpaceMode(extpart,this));
    wgtmax = _maxweight.size()>numberModes()
      ? _maxweight[numberModes()] : 1.;
    addMode(mode,wgtmax,wgt);
  }
}
