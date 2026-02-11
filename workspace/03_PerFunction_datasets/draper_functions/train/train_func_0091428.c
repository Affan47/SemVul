doinit() {
  DecayIntegrator::doinit();

  unsigned int isize=_incoming.size();
  if(isize!=_outgoing1.size()||isize!=_outgoing2.size()||
     isize!=_maxweight.size()||isize!=_coupling.size())
    throw InitException() << "Inconsistent parameters TensorMesonVectorVectorDecayer"
			  << Exception::abortnow;

  vector<double> wgt(0);
  tPDVector extpart(3);
  DecayPhaseSpaceModePtr mode;
  for(unsigned int ix=0;ix<_incoming.size();++ix) {
    extpart[0]=getParticleData(_incoming[ix]);
    extpart[1]=getParticleData(_outgoing1[ix]);
    extpart[2]=getParticleData(_outgoing2[ix]);
    if(extpart[0]&&extpart[1]&&extpart[2])
      mode=new_ptr(DecayPhaseSpaceMode(extpart,this));
    else
      mode=DecayPhaseSpaceModePtr();
    addMode(mode,_maxweight[ix],wgt);
  }
}
