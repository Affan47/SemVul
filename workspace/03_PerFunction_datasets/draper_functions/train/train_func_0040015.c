doinit() {
  DecayIntegrator::doinit();

  _current->init();

  DecayPhaseSpaceModePtr mode;
  DecayPhaseSpaceChannelPtr channel;
  tPDVector extpart,ptemp;
  extpart.push_back(getParticleData(ParticleID::tauminus));
  extpart.push_back(getParticleData(ParticleID::nu_tau));
  Energy mtau(extpart[0]->mass());
  double maxweight;
  vector<double> channelwgts;
  int iq(0),ia(0);
  _modemap.clear();
  unsigned int ix,iy;
  bool done;
  vector<double>::iterator start,end;
  for(ix=0;ix<_current->numberOfModes();++ix) {

    extpart.resize(2);
    ptemp=_current->particles(-3,ix,iq,ia);
    for(iy=0;iy<ptemp.size();++iy) extpart.push_back(ptemp[iy]);

    mode=new_ptr(DecayPhaseSpaceMode(extpart,this));

    channel = new_ptr(DecayPhaseSpaceChannel(mode));
    channel->addIntermediate(extpart[0],0,0.0,-1,1);
    done=_current->createMode(-3,ix,mode,2,1,channel,mtau);
    if(done) {


      maxweight = _wgtmax.size()>numberModes() ? _wgtmax[numberModes()] : 0;

      if(_wgtloc.size()>numberModes()&&
	 _wgtloc[numberModes()]+mode->numberChannels()<=_weights.size()) {
	start=_weights.begin()+_wgtloc[numberModes()];
	end  = start+mode->numberChannels();
	channelwgts=vector<double>(start,end);
      }
      else {
	channelwgts.resize(mode->numberChannels(),1./(mode->numberChannels()));
      }
      _modemap.push_back(ix);

      if(extpart.size()==3) {
	channelwgts.clear();
	mode=new_ptr(DecayPhaseSpaceMode(extpart,this));
      }
      addMode(mode,maxweight,channelwgts);
    }
  }
  _current->reset();
  _current->touch();
  _current->update();
}
