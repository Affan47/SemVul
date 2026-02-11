modeNumber(bool & cc,tcPDPtr parent,
				 const tPDVector & children) const {
  if(children.size()!=3) return -1;
  unsigned int npi0(0),npip(0),npim(0); int id,iother(0);
  tPDVector::const_iterator pit = children.begin();
  for( ;pit!=children.end();++pit) {
    id=(**pit).id();
    if(id==ParticleID::piplus)           ++npip;
    else if(id==ParticleID::piminus)     ++npim;
    else if(id==ParticleID::pi0&&npi0<2) ++npi0;
    else iother=id;
  }
  bool charged;
  if(npim==1&&npip==1) {
    charged=true;
    if(npi0==1) iother=ParticleID::pi0;
  }
  else if(npi0==2) charged=false;
  else return -1;

  id=parent->id();
  unsigned int ix(0);
  int imode(-1);
  do {
    if(id==_incoming[ix]&&iother==_outgoing[ix]&&_charged[ix]==charged)
      imode=ix;
    ++ix;
  }
  while(imode<0&&ix<_incoming.size());
  cc=false;
  return imode;
}
