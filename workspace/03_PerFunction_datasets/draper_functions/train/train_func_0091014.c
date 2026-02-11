modeNumber(bool & cc,tcPDPtr parent,
					const tPDVector & children) const {
  cc=false;
  int imode(-1);
  long idin(parent->id());
  if(children.size()!=3) return -1;
  unsigned int npip(0),npim(0),npi0(0);
  long idother(0),id;
  for(tPDVector::const_iterator pit=children.begin();
      pit!=children.end();++pit) {
    id=(**pit).id();
    if(id==ParticleID::piplus)       ++npip;
    else if(id==ParticleID::piminus) ++npim;
    else if(id==ParticleID::pi0)     ++npi0;
    else idother=id;
  }

  if(!((npip==1&&npim==1)||npi0==2)||idother==0) return -1;
  unsigned int ix=0;
  do {
    if(idin==_incoming[ix]&&idother==_outgoing[ix]) imode=ix;
    ++ix;
  }
  while(ix<_incoming.size()&&imode<0);
  return npi0==2 ? 2*imode+1 : 2*imode;
}
