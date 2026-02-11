createMode(int icharge, unsigned int imode,
				    DecayPhaseSpaceModePtr mode,
				    unsigned int iloc,unsigned int ires,
				    DecayPhaseSpaceChannelPtr phase,Energy upp) {
  tPDPtr part(getParticleData(_id[imode]));

  if(abs(icharge)!=abs(int(getParticleData(_id[imode])->iCharge()))) return false;

  Energy min=part->massMin();
  if(min>upp) return false;

  DecayPhaseSpaceChannelPtr newchannel(new_ptr(DecayPhaseSpaceChannel(*phase)));
  newchannel->resetDaughter(-ires,iloc);
  mode->addChannel(newchannel);
  return true;
}
