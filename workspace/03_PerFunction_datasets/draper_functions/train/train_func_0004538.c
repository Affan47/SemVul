modeNumber(bool & cc,tcPDPtr parent,
					   const tPDVector & children) const {
  if(children.size()!=2) return -1;
  int id(parent->id());
  int idbar = parent->CC() ? parent->CC()->id() : id;
  int id1(children[0]->id());
  int id1bar = children[0]->CC() ? children[0]->CC()->id() : id1;
  int id2(children[1]->id());
  int id2bar = children[1]->CC() ? children[1]->CC()->id() : id2;
  int imode(-1);
  unsigned int ix(0);
  cc=false;
  do {
    if(_incoming[ix]==id   ) {
      if((id1   ==_outgoingf[ix]&&id2   ==_outgoinga[ix])||
	 (id2   ==_outgoingf[ix]&&id1   ==_outgoinga[ix])) imode=ix;
    }
    if(_incoming[ix]==idbar) {
      if((id1bar==_outgoingf[ix]&&id2bar==_outgoinga[ix])||
	 (id2bar==_outgoingf[ix]&&id1bar==_outgoinga[ix])) {
	imode=ix;
	cc=true;
      }
    }
    ++ix;
  }
  while(imode<0&&ix<_incoming.size());
  return imode;
}
